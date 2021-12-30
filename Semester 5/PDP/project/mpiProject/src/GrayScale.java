public class GrayScale implements Transformer{
    int[][][] result;
    int[][][] imageArray;

    @Override
    public Image transformSequential(Image image) {
        if(image.getChannels() == 1)
            return image;
        for(int x=0;x<image.getWidth();x++)
            for(int y=0;y<image.getHeight();y++) {
                result[y][x][0] = computeResult(x, y);
            }
        return new Image(result);
    }

    private int computeResult(int x, int y){
        int[] rgb = imageArray[y][x];
        return (int) (0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
    }

    @Override
    public Image transformParallel(Image image) {
        if(image.getChannels() == 1)
            return image;

        Entry[][] tasks = Main.splitTasks(image.getWidth(), image.getHeight(), Settings.processes-1);
        sendTasks(tasks);
        for(int i=1;i<Settings.processes;i++){
            Integer[] results = receiveArray(i, Integer[]::new);
            for(int j=0;j<results.length;j++){
                Entry e = tasks[i-1][j];
                result[e.getY()][e.getX()][0] = results[j];
            }
        }
        return new Image(result);
    }

    @Override
    public void worker(Image image) {
        if(image.getChannels() == 1)
            return;

        Entry[] tasks = receiveTasks();
        Integer[] results = new Integer[tasks.length];
        for(int i=0;i<tasks.length;i++){
                results[i] = computeResult(tasks[i].getX(), tasks[i].getY());
        }
        sendArray(results, 0);
    }

    @Override
    public void initialise(Image image) {
        imageArray = image.getImageArray();
        if(Main.rank == 0)
            result = new int[image.getHeight()][image.getWidth()][1];
    }
}
