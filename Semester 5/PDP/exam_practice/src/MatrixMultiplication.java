import mpi.MPI;

public class MatrixMultiplication {
    public static void run(){
        int rank = MPI.COMM_WORLD.Rank();
        int nProcs = MPI.COMM_WORLD.Size();

        if(rank==0){
            int m=10, n=10;
            int[][] a = new int[n][m];
            int[][] b = new int[n][m];
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    b[i][j] = i+j;
                    if(i==j)
                        a[i][j] = 1;
                }
            }

            int[][] res = master(a, b, nProcs);
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    String space = "";
                    if(res[i][j]<10)
                        space = "  ";
                    else
                        space = " ";
                    System.out.print(res[i][j] + space);
                    if(res[i][j]!=i+j)
                        System.out.println("Mistake at " + i + " " + j);
                }
                System.out.println();
            }
            System.out.println("OK!");
        }else{
            worker(nProcs, rank);
        }
    }

    static int[][] computeResult(int[][] a, int[][] b, int nProcs, int id){
        int begin = id * (a.length + nProcs-1)/nProcs;
        int end = (id+1) * (a.length + nProcs-1)/nProcs;
        if(end>a.length)
            end = a.length;
        int [][] localRes = new int[end-begin][b[0].length];
        for(int i=begin;i<end;i++){
            for(int j=0;j<b[0].length;j++){
                int sum = 0;
                for(int k=0;k<b.length;k++){
                    sum += a[i][k] * b[k][j];
                }
                localRes[i-begin][j] = sum;
            }
        }

        return localRes;
    }

    public static int[][] master(int[][] a, int[][] b, int nProcs){
        int[][] result = new int[a.length][a[0].length];
        int[] sizes = new int[]{a.length, a[0].length};
        MPI.COMM_WORLD.Bcast(sizes, 0, 2, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(a, 0, a.length, MPI.OBJECT, 0);
        MPI.COMM_WORLD.Bcast(b, 0, b.length, MPI.OBJECT, 0);
        for(int id=0;id<nProcs;id++){
            int begin = id * (a.length + nProcs-1)/nProcs;
            int end = (id+1) * (a.length + nProcs-1)/nProcs;
            if(end>a.length)
                end = a.length;
            int[][] localRes;
            if(id==0){
                localRes = computeResult(a,b,nProcs, 0);
            }else{
                localRes = new int[end-begin][b.length];
                MPI.COMM_WORLD.Recv(localRes, 0, localRes.length, MPI.OBJECT, id, 0);
            }
            for(int i=begin;i<end;i++){
                for(int j=0;j<localRes[0].length;j++){
                    result[i][j] = localRes[i-begin][j];
                }
            }
        }
        return result;
    }

    public static void worker(int nProcs, int myId){
        int[] sizes = new int[2];
        MPI.COMM_WORLD.Bcast(sizes, 0, 2, MPI.INT, 0);
        int[][] a = new int[sizes[0]][sizes[1]];
        int[][] b = new int[sizes[0]][sizes[1]];
        MPI.COMM_WORLD.Bcast(a, 0, a.length, MPI.OBJECT, 0);
        MPI.COMM_WORLD.Bcast(b, 0, b.length, MPI.OBJECT, 0);
        int[][] localRes = computeResult(a, b, nProcs, myId);
        MPI.COMM_WORLD.Send(localRes, 0, localRes.length, MPI.OBJECT, 0, 0);
    }
}
