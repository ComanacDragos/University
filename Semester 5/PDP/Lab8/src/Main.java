import mpi.MPI;

public class Main {
    public static long START = System.nanoTime();

    public static int process, processes;
    public static void main(String[] args) {
        MPI.Init(args);
        process = MPI.COMM_WORLD.Rank();
        processes = MPI.COMM_WORLD.Size();
        System.out.println(process + "/" + processes);
        DistributedSharedMemory sharedMemory = new DistributedSharedMemory();

        sharedMemory.observe(Variable.X, 0);
        sharedMemory.observe(Variable.X, 1);

        sharedMemory.observe(Variable.Y, 0);
        sharedMemory.observe(Variable.Y, 1);

        Logger.setSharedMemory(sharedMemory);
        Thread t = new Observer(sharedMemory);
        t.start();

        try{
            switch (process) {
                case 0 -> {
                    sharedMemory.updateVariable(Variable.X, 3);
                    //Thread.sleep(200);
                    sharedMemory.compareAndExchange(Variable.X, 7, 10);
                    sharedMemory.close();
                }
                case 1 -> {
                    Thread.sleep(100);
                    sharedMemory.updateVariable(Variable.X, 7);
                    sharedMemory.close();
                }
            }


            t.join();
        }catch (InterruptedException e){
            e.printStackTrace();
        }
        MPI.Finalize();
    }
}
