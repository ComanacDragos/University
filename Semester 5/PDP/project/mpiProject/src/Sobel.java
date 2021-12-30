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
                result[y][x][0] = computeGradient(x, y);
            }
        return new Image(result);
    }

    private int computeGradient(int x, int y){
        int s1 = gx.getImageArray()[y][x][0];
        int s2 = gy.getImageArray()[y][x][0];
        double gradient = Math.sqrt(Math.pow(s1, 2)+Math.pow(s2, 2));
        if(gradient > threshold){
             return 128;//(int)gradient;
        }else{
            return 0;
        }
    }

    @Override
    public void initialise(Image image) {
        if(image.getChannels() != 1)
            throw new RuntimeException("Image must be grayscale");
        gx = broadcastImage(sobelV.transform(image));
        gy = broadcastImage(sobelH.transform(image));
        if(Main.rank == 0)
            result = new int[image.getHeight()][image.getWidth()][1];
    }


    @Override
    public Image transformParallel(Image image) {
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
        Entry[] tasks = receiveTasks();
        Integer[] results = new Integer[tasks.length];
        for(int i=0;i<tasks.length;i++){
            results[i] = computeGradient(tasks[i].getX(), tasks[i].getY());
        }
        sendArray(results, 0);
    }

}
