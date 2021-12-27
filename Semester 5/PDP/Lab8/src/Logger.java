import mpi.MPI;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
    static int process = MPI.COMM_WORLD.Rank();
    static boolean append = false;
    static DistributedSharedMemory sharedMemory;

    public static void setSharedMemory(DistributedSharedMemory sharedMemory) {
        Logger.sharedMemory = sharedMemory;
    }

    public synchronized static void log(Object obj){
        System.out.println(process + ". " + obj.toString());
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("E:\\University\\Semester 5\\PDP\\Lab8\\output\\" + process + ".out", append)))){
            writer.println(Thread.currentThread().getId()  + ". " + obj.toString() + "\n" + sharedMemory + "\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
        append = true;
    }
}
