import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Convolution implements Transformer{
    double[][] filter;
    int[][][] result;
    int[][][] imageArray;

    public Convolution(double[][] filter) {
        this.filter = filter;
    }

    @Override
    public Image transformSequential(Image image) {
        //long start = System.currentTimeMillis();
        for(int x=0;x<image.getWidth();x++)
            for(int y=0;y<image.getHeight();y++)
                for(int c=0;c<image.getChannels();c++){
                    computeConvolution(x, y, c);
                }
        //System.out.println("Seq time: " + (System.currentTimeMillis() - start));
        return new Image(result);
    }

    private void computeConvolution(int x, int y, int c){
        int sum = 0;
        int halfFilter = filter.length/2;
        for(int fy=-halfFilter;fy<=halfFilter;fy++)
            for(int fx=-halfFilter;fx<=halfFilter;fx++){
                int valueFromImage;
                if(x+fx<0 || x+fx>=imageArray[0].length || y+fy<0 || y+fy>=imageArray.length)
                    valueFromImage = 0;
                else
                    valueFromImage = imageArray[y+fy][x+fx][c];
                sum += valueFromImage * filter[fy+halfFilter][fx+halfFilter];
            }
        result[y][x][c] = sum;
    }

    @Override
    public Image transformParallel(Image image) {
        List<List<Entry>> tasks = Main.splitTasks(image.getWidth(), image.getHeight());
        //long start = System.currentTimeMillis();
        ExecutorService executorService = Executors.newFixedThreadPool(Settings.threads);
        tasks.forEach(task -> executorService.execute(new Worker(task, image.getChannels())));
        executorService.shutdown();
        try {
            executorService.awaitTermination(1, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        //System.out.println("Parallel: " + (System.currentTimeMillis() - start));
        return new Image(result);
    }

    @Override
    public void initialise(Image image) {
        imageArray = image.getImageArray();
        result = new int[image.getHeight()][image.getWidth()][image.getChannels()];
    }

    public class Worker implements Runnable{
        List<Entry> tasks;
        int channels;

        public Worker(List<Entry> tasks, int channels) {
            this.tasks = tasks;
            this.channels = channels;
        }

        @Override
        public void run(){
            long start = System.currentTimeMillis();
            for(Entry entry:tasks)
                for(int c=0;c<channels;c++)
                    computeConvolution(entry.getX(), entry.getY(), c);
            //System.out.println(Thread.currentThread().getId() + " :: " + (System.currentTimeMillis()-start) + " " + tasks.size());
        }
    }
}
