import mpi.MPI;

public class Main {
    public static void main(String[] args) {
        MPI.Init(args);
        Power.run();
        MPI.Finalize();
    }
}