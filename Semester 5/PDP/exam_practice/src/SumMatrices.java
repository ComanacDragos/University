import mpi.MPI;

public class SumMatrices {
    static void run(){
        int rank = MPI.COMM_WORLD.Rank();
        int nrProcs = MPI.COMM_WORLD.Size();

        if(rank == 0){
            int[][] a = new int[10][10];
            int[][] b = new int[10][10];
            for(int i=0;i<10;i++)
                for(int j=0;j<10;j++){
                    a[i][j] = j;
                    b[i][j] = -j;
                }
            int[][] res = sum(a, b, nrProcs);
            boolean ok = true;
            for(int i=0;i<10;i++)
                for(int j=0;j<10;j++) {
                    if(res[i][j] != 0){
                        System.out.println("Mistake at  " + i + " " + j);
                        ok=false;
                    }
                }
            if(ok)
                System.out.println("OK!");
        }else{
            worker(rank, nrProcs);
        }
    }

    static int[][] computeSum(int[][] a, int[][] b, int nrProcs, int myId){
        int begin = myId*(a.length+nrProcs-1)/nrProcs;
        int end = (myId + 1)*(a.length+nrProcs-1)/nrProcs;
        if(end>a.length)
            end=a.length;
        System.out.println(myId + " computing: " + begin + " -> " + (end-1));

        int[][] result = new int[end-begin][a[0].length];
        for(int i=begin;i<end;i++){
            for(int j=0;j<a[0].length;j++)
                result[i-begin][j] = a[i][j] + b[i][j];
        }
        return result;
    }

    static int[][] sum(int[][] a, int[][] b, int nrProcs){
        int[][] result = new int[a.length][a[0].length];
        int[] sizes = new int[2];
        sizes[0] = a.length;
        sizes[1] = a[0].length;
        MPI.COMM_WORLD.Bcast(sizes, 0, 2, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(a, 0, a.length, MPI.OBJECT, 0);
        MPI.COMM_WORLD.Bcast(b, 0, a.length, MPI.OBJECT, 0);

        for(int id=0;id<nrProcs;id++){
            int[][] localRes;
            if(id==0)
                localRes = computeSum(a, b, nrProcs, 0);
            else{
                int[] resSize = new int[2];
                MPI.COMM_WORLD.Recv(resSize, 0, 2, MPI.INT, id, 0);
                localRes = new int[resSize[0]][resSize[1]];
                MPI.COMM_WORLD.Recv(localRes, 0, resSize[0], MPI.OBJECT, id, 0);
            }
            int begin = id*(a.length+nrProcs-1)/nrProcs;
            for(int i=0;i<localRes.length;i++){
                for(int j=0;j<localRes[0].length;j++)
                    result[i+begin][j] = localRes[i][j];
            }
        }
        return result;
    }

    static void worker(int myId, int nrProcs){
        int[] sizes = new int[2];
        MPI.COMM_WORLD.Bcast(sizes, 0, 2, MPI.INT, 0);
        int[][] a = new int[sizes[0]][sizes[1]];
        MPI.COMM_WORLD.Bcast(a, 0, a.length, MPI.OBJECT, 0);
        int[][] b = new int[sizes[0]][sizes[1]];
        MPI.COMM_WORLD.Bcast(b, 0, a.length, MPI.OBJECT, 0);
        int[][] myRes = computeSum(a, b, nrProcs, myId);
        MPI.COMM_WORLD.Send(new int[]{myRes.length, myRes[0].length}, 0, 2, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Send(myRes, 0, myRes.length, MPI.OBJECT, 0, 0);

    }
}
