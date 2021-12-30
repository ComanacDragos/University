import mpi.MPI;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static int rank;
    public static void main(String[] args) {
        MPI.Init(args);
        Settings.processes = MPI.COMM_WORLD.Size();
        rank = MPI.COMM_WORLD.Rank();
        test();

        MPI.Finalize();
    }

    public static void testPerformance(){
        Settings.debugMode = false;
        Solver solver = new Solver();
        for(int size: List.of(500, 1000, 2000)){
            Image image = null;
            if(rank == 0)
                image = new Image(size, size, 3);
            solver.transform(image);
            Logger.logToConsole("Done with image of size " + size);
        }
    }

    public static void test(){
        Settings.debugMode = true;
        Image img = null;
        if(rank == 0) {
            img = new Image("E:\\University\\Semester 5\\PDP\\project\\mpi\\data\\cameraman.jpg");
            //Image img = new Image(3000, 3000, 3);
            System.out.println(img.getWidth() + "  " + img.getHeight());
        }
        GaussianBlur blur = new GaussianBlur();
        GrayScale grayScale = new GrayScale();
        Sobel sobel = new Sobel(150);
        Hough hough = new Hough(100, 10);
        Solver solver = new Solver();
        //solver.transform(img);
//        img = grayScale.transform(img);
//        img = sobel.transform(img);
//        if(rank==0)
//            new DisplayImage(img);

        Transformer trans = solver;

        //long start = System.currentTimeMillis();
        img = trans.transform(img);
        //if(rank==0)
        //    new DisplayImage(img);
        //System.out.println("MPI: " + (System.currentTimeMillis()-start));
    }

    public static Entry[][] splitTasks(Integer w, Integer h, int processes){
        int elements = w * h;
        int chunk = elements / processes;
        int rest = elements % processes;
        Entry[][] split = new Entry[processes][];
        int splitIndex = 0;
        int subsplitIndex = 0;
        Entry[] subSplit = new Entry[chunk+(rest>0?1:0)];
        for (int j = 0; j < h; j++){
            for (int i = 0; i < w; i++){
                subSplit[subsplitIndex++] = new Entry(i, j);
                if(subsplitIndex == chunk){
                    if(rest > 0){
                        i++;
                        if(i == w) {
                            j++;
                            i=0;
                        }
                        subSplit[subsplitIndex++] = new Entry(i, j);
                        rest--;
                    }
                    split[splitIndex++] = subSplit;
                    subSplit = new Entry[chunk+(rest>0?1:0)];
                    subsplitIndex = 0;
                }
            }
        }
        return split;
    }
}
