import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Sobel implements Transformer{
    int[][][] result;
    Image gx, gy;

    Convolution sobelH = new Convolution(new double[][]{
            {1., 2., 1.},
            {0., 0., 0.},
            {-1., -2., -1.},
    });
    Convolution sobelV = new Convolution(new double[][]{
            {1., 0., -1.},
            {2., 0., -2.},
            {1.,0., -1.},
    });

    int threshold;

    public Sobel(int threshold){
        this.threshold = threshold;
    }

    @Override
    public Image transformSequential(Image image) {
        for(int x=0;x<image.getWidth();x++)
            for(int y=0;y<image.getHeight();y++) {
               computeGradient(x, y);
            }
        return new Image(result);
    }

    private void computeGradient(int x, int y){
        int s1 = gx.getImageArray()[y][x][0];
        int s2 = gy.getImageArray()[y][x][0];
        double gradient = Math.sqrt(Math.pow(s1, 2)+Math.pow(s2, 2));
        if(gradient > threshold){
            result[y][x][0] = 128;//(int)gradient;
        }
    }

    @Override
    public void initialise(Image image) {
        if(image.getChannels() != 1)
            throw new RuntimeException("Image must be grayscale");
        gx = sobelV.transform(image);
        gy = sobelH.transform(image);
        result = new int[image.getHeight()][image.getWidth()][1];
    }

    @Override
    public Image transformParallel(Image image) {
        List<List<Entry>> tasks = Main.splitTasks(image.getWidth(), image.getHeight());
        ExecutorService executorService = Executors.newFixedThreadPool(Settings.threads);
        tasks.forEach(task -> executorService.execute(new Worker(task)));
        executorService.shutdown();
        try {
            executorService.awaitTermination(1, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return new Image(result);
    }

    public class Worker implements Runnable{
        List<Entry> tasks;

        public Worker(List<Entry> tasks) {
            this.tasks = tasks;
        }

        @Override
        public void run(){
            tasks.forEach(task -> computeGradient(task.getX(), task.getY()));
        }
    }
}
