import mpi.MPI;
import mpi.Status;

public class Power {
    public static void run(){
        int myId = MPI.COMM_WORLD.Rank();
        int nProcs = MPI.COMM_WORLD.Size();
        if(myId == 0){
            int[][] a = new int[][]{
                {1,2,0},
                {3,1,1},
                {0,2,1}
            };
            int n=15;
            master(n, a, nProcs);
            int[][] check = new int[a.length][a.length];
            for(int i=0;i<a.length;i++)
                for(int j=0;j<a.length;j++)
                    check[i][j] = a[i][j];
            for(int i=1;i<n;i++){
                check = multiply(a, check);
            }
            System.out.println();
            print(check);
        }else{
            worker(myId, nProcs);
        }
    }

    static int[][] multiply(int[][] a, int[][] b){
        int[][] res = new int[a.length][b[0].length];
        for(int i=0;i<a.length;i++)
            for(int j=0;j<b[0].length;j++)
                for(int k=0;k<b.length;k++){
                    res[i][j] += a[i][k] * b[k][j];
                }
        return res;
    }

    static int[][] back(int n, int[][] a, int nProcs, int myId){
        //System.out.println("enter back " + myId + " with n: " + n);
        if(n==1){
            return a;
        }
        if(n==2){
            return multiply(a, a);
        }
        int[][] res;
        int child = myId + nProcs/2;
        //if(child == MPI.COMM_WORLD.Size() && child-1 != myId)
        //    child-=1;
        if(nProcs>=2 && child<nProcs){
            //System.out.println("Sending...");
            MPI.COMM_WORLD.Send(new int[]{1}, 0, 1, MPI.INT, child, 0);
            MPI.COMM_WORLD.Send(new int[]{n/2, a.length}, 0, 2, MPI.INT, child, 1);
            MPI.COMM_WORLD.Send(a, 0, a.length, MPI.OBJECT, child, 2);
            int[][] myRes = back(n/2, a, nProcs/2, myId);
            int[][] otherRes = new int[a.length][a.length];
            MPI.COMM_WORLD.Recv(otherRes, 0, a.length, MPI.OBJECT, child, 3);
            if(n%2==0){
                res = multiply(myRes, otherRes);
            }else{
                res = multiply(
                  multiply(myRes, otherRes),
                  a
                );
            }
        }else{
            if(n%2==0){
                res = multiply(
                        back(n/2, a, nProcs, myId),
                        back(n/2, a, nProcs, myId)
                );
            }else{
                res = multiply(
                        multiply(
                                back(n/2, a, nProcs, myId),
                                back(n/2, a, nProcs, myId)
                        ),
                        a
                );
            }
        }
        return res;
    }

    static void print(int[][] res){
        for(int i=0;i<res.length;i++){
            for(int j=0;j<res[0].length;j++){
                int aux = res[i][j];
                int nDigits = 0;
                while (aux!=0){
                    aux/=10;
                    nDigits++;
                }
                String space = "";
                for(int k=0;k<15-nDigits;k++)
                    space += " ";
                System.out.print(res[i][j] + space);
            }
            System.out.println();
        }
    }

    static void master(int n, int[][] a, int nProcs){
        int[][] res = back(n, a, nProcs, 0);
        for(int i=1;i<nProcs;i++){
            MPI.COMM_WORLD.Send(new int[]{0}, 0, 1, MPI.INT, i, 0);
        }
        print(res);
    }

    static void worker(int myId, int nProcs){
        int[] alive = new int[1];
        while (true){
            //System.out.println(myId + " waiting...");
            Status status = MPI.COMM_WORLD.Recv(alive, 0, 1, MPI.INT, MPI.ANY_SOURCE, 0);
            if(alive[0] == 0){
                break;
            }
            //System.out.println("Alive! " + myId);
            int[] sizes = new int[2];
            MPI.COMM_WORLD.Recv(sizes, 0, 2, MPI.INT, status.source, 1);
            //System.out.println("Received sizes " + myId);
            int[][] a = new int[sizes[1]][sizes[1]];
            MPI.COMM_WORLD.Recv(a, 0, a.length, MPI.OBJECT, status.source, 2);
            //System.out.println("Received matrix " + myId);
            int[][] myRes = back(sizes[0], a, nProcs, myId);
            MPI.COMM_WORLD.Send(myRes, 0, myRes.length, MPI.OBJECT, status.source, 3);
        }
    }
}
