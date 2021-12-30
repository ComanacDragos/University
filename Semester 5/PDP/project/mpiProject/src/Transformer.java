import mpi.MPI;

import java.util.Arrays;
import java.util.function.Function;
import java.util.function.Supplier;

public interface Transformer {
    default Image broadcastImage(Image image){
        Image img;
        if(Main.rank == 0){
            img = image;
            MPI.COMM_WORLD.Bcast(new int[]{image.getHeight()}, 0, 1, MPI.INT, 0);
            MPI.COMM_WORLD.Bcast(image.getImageArray(), 0, image.getHeight(), MPI.OBJECT, 0);
        }else{
            int[][][] arr;
            int[] len = new int[1];
            MPI.COMM_WORLD.Bcast(len, 0, 1, MPI.INT, 0);
            arr = new int[len[0]][][];
            MPI.COMM_WORLD.Bcast(arr, 0, len[0], MPI.OBJECT, 0);
            img = new Image(arr);
        }
        return img;
    }

    default Image transform(Image image){
        Image img = broadcastImage(image);
        initialise(img);
        if(Main.rank == 0){
            if(Settings.processes == 1)
                return transformSequential(img);
            return transformParallel(img);
        }else{
            worker(img);
            return null;
        }
    }
    Image transformSequential(Image image);
    Image transformParallel(Image image);
    default void initialise(Image image){}
    default void worker(Image image){}

    default void sendTasks(Entry[][] tasks){
        for(int i=0;i<tasks.length;i++){
            sendArray(tasks[i], i+1);
        }
    }

    default Entry[] receiveTasks(){
        return receiveArray(0, Entry[]::new);

    }

    default <T> void sendArray(T[] arr, int process){
        MPI.COMM_WORLD.Send(new int[]{arr.length}, 0, 1, MPI.INT, process, 0);
        MPI.COMM_WORLD.Send(arr, 0, arr.length, MPI.OBJECT, process, 0);
    }

    default <T> T[] receiveArray(int fromProcess, Function<Integer, T[]> constructor){
        T[] tasks;
        int[] len = new int[1];
        MPI.COMM_WORLD.Recv(len, 0, 1, MPI.INT, fromProcess, 0);
        tasks = constructor.apply(len[0]);
        MPI.COMM_WORLD.Recv(tasks, 0, len[0], MPI.OBJECT, fromProcess, 0);
        return tasks;
    }


}
