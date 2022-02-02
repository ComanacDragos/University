import mpi.MPI;
import mpi.Status;

import java.util.ArrayList;
import java.util.List;

public class Combinations {
    public static void run(){
        int rank = MPI.COMM_WORLD.Rank();
        int nProcs = MPI.COMM_WORLD.Size();
        if(rank == 0){
            int n = 20;
            int k = 4;
            master(nProcs, n, k);
        }else{
            worker(rank, nProcs);
        }
    }

    static List<List<Integer>> back(List<Integer> solution, int n, int k, int myId, int nProcs){
        if(solution.size() == k){
            //System.out.println("Found solution: " + solution + " by " + myId);
            List<List<Integer>> ret = new ArrayList<>();
            ret.add(new ArrayList<>(solution));
            return ret;
        }
        List<Integer> temp = new ArrayList<>(solution);
        int child = myId + nProcs/2;
        List<List<Integer>> acc = new ArrayList<>();

        //System.out.println(myId+ " - " + child + " - " + nProcs);
        if(nProcs>=2 && child<nProcs){
            //if(child >= MPI.COMM_WORLD.Size())
            //    child = MPI.COMM_WORLD.Size()-1;
            MPI.COMM_WORLD.Send(new int[]{1}, 0, 1, MPI.INT, child, 0);
            MPI.COMM_WORLD.Send(new Object[]{new ArrayList<>(solution)}, 0, 1, MPI.OBJECT, child, 1);
            for(int i=1;i<=n;i+=2){
                if(temp.size()==0 || temp.get(temp.size()-1) < i){
                    temp.add(i);
                    acc.addAll(back(temp, n, k, myId, nProcs/2));
                    temp.remove(temp.size()-1);
                }
            }
            Object[] receivedData = new Object[1];
            //System.out.println(myId + " waiting for " + child + " with nprocs " + nProcs);
            MPI.COMM_WORLD.Recv(receivedData, 0, 1, MPI.OBJECT, child, 2);
            //System.out.println(myId + " done waiting for " + child + " with nprocs " + nProcs);
            acc.addAll((List<List<Integer>>) receivedData[0]);
        }else{
            for(int i=1;i<=n;i++){
                if(temp.size()==0 || temp.get(temp.size()-1) < i){
                    temp.add(i);
                    acc.addAll(back(temp, n, k, myId, nProcs/2));
                    temp.remove(temp.size()-1);
                }
            }
        }
        return acc;
    }

    static void master(int nProcs, int n, int k){
        MPI.COMM_WORLD.Bcast(new int[]{n, k}, 0, 2, MPI.INT, 0);
        List<List<Integer>> combinations = back(new ArrayList<>(), n, k, 0, nProcs);
        for(int i=1;i<nProcs;i++){
            MPI.COMM_WORLD.Send(new int[]{0}, 0, 1, MPI.INT, i, 0);
        }
        combinations.stream().sorted((a, b)->{
            for(int i=0;i<a.size();i++){
                if(!a.get(i).equals(b.get(i)))
                    return a.get(i)-b.get(i);
            }
            return 0;
        }).forEach(System.out::println);
        System.out.println("Total: " + combinations.size());
    }

    static void worker(int myId, int nProcs){
        int[] combData = new int[2];
        MPI.COMM_WORLD.Bcast(combData, 0, 2, MPI.INT, 0);
        int n = combData[0];
        int k = combData[1];
        int[] alive = new int[1];
        while(true){
            //System.out.println(myId + " waiting...");
            Status status = MPI.COMM_WORLD.Recv(alive, 0, 1, MPI.INT, MPI.ANY_SOURCE, 0);
            if(alive[0] == 0){
                break;
            }
            System.out.println("Starting  " + myId + " waiting for " + status.source);
            Object[] data = new Object[1];
            MPI.COMM_WORLD.Recv(data, 0, 1, MPI.OBJECT, status.source, 1);
            //System.out.println("Starting done  " + myId + " waiting for " + status.source);

            List<Integer> temp = (List<Integer>) data[0];
            List<List<Integer>> acc = new ArrayList<>();
            for(int i=2;i<=n;i+=2){
                if(temp.size()==0 || temp.get(temp.size()-1) < i){
                    temp.add(i);
                    acc.addAll(back(temp, n, k, myId, nProcs));
                    temp.remove(temp.size()-1);
                }
            }
            MPI.COMM_WORLD.Send(new Object[]{acc}, 0, 1, MPI.OBJECT, status.source, 2);
        }
    }
}
