import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class GrayScale implements Transformer{
    int[][][] result;
    int[][][] imageArray;

    @Override
    public Image transformSequential(Image image) {
        if(image.getChannels() == 1)
            return image;
        for(int x=0;x<image.getWidth();x++)
            for(int y=0;y<image.getHeight();y++) {
                computeResult(x, y);
            }
        return new Image(result);
    }

    private void computeResult(int x, int y){
        int[] rgb = imageArray[y][x];
        result[y][x][0] = (int) (0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
    }

    @Override
    public Image transformParallel(Image image) {
        if(image.getChannels() == 1)
            return image;
        Entry[][] tasks = Main.splitTasks(image.getWidth(), image.getHeight(), Settings.processes);

        return new Image(result);
    }

    @Override
    public void initialise(Image image) {
        imageArray = image.getImageArray();
        if(Main.rank == 0)
            result = new int[image.getHeight()][image.getWidth()][1];
    }
}
