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
                    result[y][x][c] = computeConvolution(x, y, c);
                }
        //System.out.println("Seq time: " + (System.currentTimeMillis() - start));
        return new Image(result);
    }

    private int computeConvolution(int x, int y, int c){
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
        return sum;
    }

    @Override
    public Image transformParallel(Image image) {
        Entry[][] tasks = Main.splitTasks(image.getWidth(), image.getHeight(), Settings.processes-1);
        sendTasks(tasks);
        for(int i=1;i<Settings.processes;i++){
            Integer[][] results = receiveArray(i, Integer[][]::new);
            for(int j=0;j<results.length;j++){
                Entry e = tasks[i-1][j];
                for(int c=0;c<image.getChannels();c++)
                    result[e.getY()][e.getX()][c] = results[j][c];
            }
        }
        return new Image(result);
    }

    @Override
    public void worker(Image image) {
        Entry[] tasks = receiveTasks();
        Integer[][] results = new Integer[tasks.length][image.getChannels()];
        for(int i=0;i<tasks.length;i++){
            for(int c=0;c<image.getChannels();c++)
                results[i][c] = computeConvolution(tasks[i].getX(), tasks[i].getY(), c);
        }
        sendArray(results, 0);
    }

    @Override
    public void initialise(Image image) {
        imageArray = image.getImageArray();
        if(Main.rank == 0)
            result = new int[image.getHeight()][image.getWidth()][image.getChannels()];
    }
}
