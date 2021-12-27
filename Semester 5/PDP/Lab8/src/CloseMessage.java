import mpi.MPI;

public class CloseMessage extends Message{
    int process = MPI.COMM_WORLD.Rank();

    @Override
    public String toString() {
        return "Close";
    }

    @Override
    public void action(DistributedSharedMemory sharedMemory) {

    }
}
