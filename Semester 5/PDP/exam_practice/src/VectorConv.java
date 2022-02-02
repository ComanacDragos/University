import mpi.MPI;

import java.util.Arrays;

public class VectorConv {
    static void run(){
        int rank = MPI.COMM_WORLD.Rank();
        int nProcs = MPI.COMM_WORLD.Size();

        if(rank == 0){
            int[] a = new int[]{1,2,3};
            int[] b = new int[]{1,2,3};
            System.out.println(Arrays.toString(conv(a, b, nProcs)));
        }else{
            worker(rank, nProcs);
        }
    }

    static int[] compute(int[] a, int[] b, int nrProcs, int myId){
        int totalSize = a.length + b.length - 1;
        int begin = myId * (totalSize -1 + nrProcs)/nrProcs;
        int end = (myId +1) * (totalSize -1 + nrProcs)/nrProcs;
        if(end>totalSize){
            end = totalSize;
        }
        System.out.println(myId + " " + begin + "->" + end);
        int[] res = new int[end-begin];
        for(int k=begin;k<end;k++){
            for(int i=0;i<a.length;i++){
                if(k-i>=0 && k-i<a.length) {
                    res[k - begin] += a[i] * b[k - i];
                }
            }
        }
        return res;
    }

    static int[] conv(int[] a, int[] b, int nrProcs){
        int[] res = new int [a.length+b.length-1];
        MPI.COMM_WORLD.Bcast(new int[]{a.length}, 0, 1, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(a, 0, a.length, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(b, 0, b.length, MPI.INT, 0);
        for(int id=0;id<nrProcs;id++){
            int begin = id * (res.length + nrProcs-1)/nrProcs;
            int[] localRes;
            if(id==0){
                localRes = compute(a,b, nrProcs, 0);
            }else{
                int end = (id +1) * (res.length + nrProcs-1)/nrProcs;
                if(end>res.length)
                    end = res.length;
                localRes = new int[end-begin];
                MPI.COMM_WORLD.Recv(localRes, 0, end-begin, MPI.INT, id, 0);
            }
            for(int i=0;i<localRes.length;i++)
                res[i+begin] = localRes[i];
        }
        return res;
    }

    static void worker(int myId, int nrProcs){
        int[] sizes = new int[1];
        MPI.COMM_WORLD.Bcast(sizes, 0, 1, MPI.INT, 0);
        int[] a = new int[sizes[0]];
        MPI.COMM_WORLD.Bcast(a, 0, a.length, MPI.INT, 0);
        int[] b = new int[sizes[0]];
        MPI.COMM_WORLD.Bcast(b, 0, b.length, MPI.INT, 0);
        int[] myRes = compute(a, b, nrProcs, myId);
        MPI.COMM_WORLD.Send(myRes, 0, myRes.length, MPI.INT, 0, 0);
    }
}
