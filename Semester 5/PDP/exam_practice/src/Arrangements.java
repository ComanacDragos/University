import mpi.MPI;
import mpi.Status;

import java.util.ArrayList;
import java.util.List;

public class Arrangements {
    public static void run(){
        int rank = MPI.COMM_WORLD.Rank();
        int nProcs = MPI.COMM_WORLD.Size();
        int n = 6;
        int k = 2;
        if(rank == 0){
            master(nProcs, n, k);
        }else{
            worker(rank, nProcs, n, k);
        }
    }

    static int back(List<Integer> solution, int n, int k, int myId, int nProcs){
        if(solution.size() == k){
            System.out.println("Found sol " + solution);
            return 1;
        }
        int child = myId + nProcs/2;
        int sum = 0;
        List<Integer> temp = new ArrayList<>(solution);
        if(nProcs>=2 && child<nProcs){
            MPI.COMM_WORLD.Send(new int[]{1}, 0, 1, MPI.INT, child, 0);
            MPI.COMM_WORLD.Send(new Object[]{new ArrayList<>(solution)}, 0, 1, MPI.OBJECT, child, 1);
            for(int i=1;i<=n;i+=2){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                sum+=back(temp, n, k, myId, nProcs/2);
                temp.remove(temp.size()-1);
            }
            int[] data = new int[1];
            MPI.COMM_WORLD.Recv(data, 0,1,MPI.INT, child, 2);
            sum += data[0];
        }else{
            for(int i=1;i<=n;i++){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                sum+=back(temp, n, k, myId, nProcs);
                temp.remove(temp.size()-1);
            }
        }
        return sum;
    }

    static void master(int nProcs, int n, int k){
        int sum = back(new ArrayList<>(), n, k, 0, nProcs);
        for(int i=1;i<nProcs;i++)
            MPI.COMM_WORLD.Send(new int[]{0}, 0, 1, MPI.INT, i, 0);
        System.out.println("Found: " + sum);
    }

    static void worker(int myId, int nProcs, int n, int k){
        int[] alive = new int[1];
        while (true){
            Status status = MPI.COMM_WORLD.Recv(alive, 0, 1, MPI.INT, MPI.ANY_SOURCE, 0);
            if(alive[0] == 0)
                break;
            Object[] data = new Object[1];
            MPI.COMM_WORLD.Recv(data, 0, 1, MPI.OBJECT, status.source, 1);
            List<Integer> temp = (List<Integer>)data[0];
            int sum = 0;
            for(int i=2;i<=n;i+=2){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                sum += back(temp, n, k, myId, nProcs);
                temp.remove(temp.size()-1);
            }
            MPI.COMM_WORLD.Send(new int[]{sum}, 0, 1, MPI.INT, status.source, 2);
        }
    }
}
