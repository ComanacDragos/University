import mpi.MPI;


public class Main {
    public static void main(String[] args) {
        runRegular(args);
    }

    public static void runRegular(String[] args){
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.Rank();
        int processes = MPI.COMM_WORLD.Size();

        System.out.println("-> " + rank + "/" + processes);
        if(rank == 0){

        }else{

        }
        MPI.Finalize();
    }


    public static void generatePolynomials(int degree1, int degree2){
        new Polynomial(degree1, "data/p1.txt");
        new Polynomial(degree2, "data/p2.txt");
    }
}
