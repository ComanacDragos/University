import mpi.MPI;
import mpi.Status;

import java.util.ArrayList;
import java.util.List;

public class Permutations {
    public static void run(){
        int rank = MPI.COMM_WORLD.Rank();
        int nProcs = MPI.COMM_WORLD.Size();
        int n = 8;
        if(rank==0){
            long start = System.currentTimeMillis();
            master(n, nProcs);
            System.out.println("Time: " + (System.currentTimeMillis()-start)/1000.0);
        }else{
            worker(rank, nProcs);
        }
    }

    static int back(List<Integer> sol, int n, int myId, int nProcs){
        if(sol.size() == n){
            System.out.println("Found solution: " + sol + " by " + myId);
            return 1;
        }
        int sum = 0;
        List<Integer> temp = new ArrayList<>(sol);
        int child = myId + nProcs/2;
        if(nProcs>=2 && child < nProcs){
            MPI.COMM_WORLD.Send(new int[]{1}, 0, 1, MPI.INT, child, 0);
            MPI.COMM_WORLD.Send(new Object[]{new ArrayList<>(sol)}, 0, 1, MPI.OBJECT, child, 1);
            for(int i=1;i<=n;i+=2){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                sum+=back(temp, n, myId, nProcs/2);
                temp.remove(temp.size()-1);
            }
            int[] recvCount = new int[1];
            MPI.COMM_WORLD.Recv(recvCount, 0, 1, MPI.INT, child, 2);
            sum += recvCount[0];
        }else{
            for(int i=1;i<=n;i++){
                if(temp.contains(i))
                    continue;
                temp.add(i);
                sum+=back(temp, n, myId, nProcs/2);
                temp.remove(temp.size()-1);
            }
        }
        return sum;
    }

    static void master(int n, int nProcs){
        MPI.COMM_WORLD.Bcast(new int[]{n}, 0, 1, MPI.INT, 0);
        int sum = back(new ArrayList<>(), n, 0, nProcs);
        for(int i=1;i<nProcs;i++){
            MPI.COMM_WORLD.Send(new int[]{0}, 0, 1, MPI.INT, i, 0);
        }
        System.out.println("Final count: " + sum);
    }

    static void worker(int myId, int nProcs){
        int[] n = new int[1];
        MPI.COMM_WORLD.Bcast(n, 0, 1, MPI.INT, 0);
        int[] alive = new int[1];
        while (true){
            Status recv = MPI.COMM_WORLD.Recv(alive, 0, 1, MPI.INT, MPI.ANY_SOURCE, 0);
            if(alive[0] == 0)
                break;
            int parent = recv.source;
            Object[] receivedData = new Object[1];
            MPI.COMM_WORLD.Recv(receivedData, 0, 1, MPI.OBJECT, parent, 1);
            List<Integer> sol = (List<Integer>) receivedData[0];
            int sum = 0;
            for(int i=2;i<=n[0];i+=2){
                if(sol.contains(i))
                    continue;
                sol.add(i);
                sum += back(sol, n[0], myId, nProcs);
                sol.remove(sol.size()-1);
            }
            MPI.COMM_WORLD.Send(new int[]{sum}, 0, 1, MPI.INT, parent, 2);
        }
    }
}
