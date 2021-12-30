import mpi.MPI;

import java.util.*;

/*
https://github.com/davidchatting/hough_lines/blob/master/HoughTransform.java
 */
public class Hough implements Transformer{
    // The size of the neighbourhood in which to search for other local maxima
    final int neighbourhoodSize = 4;

    // How many discrete values of theta shall we check?
    final int maxTheta = 180;

    // Using maxTheta, work out the step
    final double thetaStep = Math.PI / maxTheta;

    // the width and height of the image
    protected int width, height;

    // the hough array
    protected Integer[][] houghArray;

    // the coordinates of the centre of the image
    protected float centerX, centerY;

    // the height of the hough array
    protected int houghHeight;

    // double the hough height (allows for negative numbers)
    protected int doubleHeight;

    // the number of points that have been added
    protected int numPoints;

    // cache of values of sin and cos for different theta values. Has a significant performance improvement.
    private double[] sinCache;
    private double[] cosCache;

    int[][][] result;
    int[][][] imageArray;

    int threshold, noLines;

    public Hough(int threshold, int noLines){
        this.threshold = threshold;
        this.noLines = noLines;
    }

    @Override
    public void initialise(Image image) {
        if(image.getChannels()!=1)
            throw new RuntimeException("Image must be grayscale");

        if(Main.rank == 0)
            result = new int[image.getHeight()][image.getWidth()][1];
        imageArray = image.getImageArray();

        this.width = image.getWidth();
        this.height = image.getHeight();

        // Calculate the maximum height the hough array needs to have
        houghHeight = (int) (Math.sqrt(2) * Math.max(height, width)) / 2;

        // Double the height of the hough array to cope with negative r values
        doubleHeight = 2 * houghHeight;

        // Create the hough array
        houghArray = new Integer[maxTheta][doubleHeight];
        for(int i=0;i<maxTheta;i++)
            for(int j=0;j<doubleHeight;j++)
                houghArray[i][j] = 0;

        // Find edge points and vote in array
        centerX = (float)width / 2;
        centerY = (float)height / 2;

        // Count how many points there are
        numPoints = 0;

        // cache the values of sin and cos for faster processing
        sinCache = new double[maxTheta];
        cosCache = sinCache.clone();
        for (int t = 0; t < maxTheta; t++) {
            double realTheta = t * thetaStep;
            sinCache[t] = Math.sin(realTheta);
            cosCache[t] = Math.cos(realTheta);
        }
    }

    /**
     * Adds points from an image. The image is assumed to be greyscale black and white, so all pixels that are
     * not black are counted as edges. The image should have the same dimensions as the one passed to the constructor.
     */
    public void addPoints(Image image) {

        // Now find edge points and update the hough array
        for (int x = 0; x < image.getWidth(); x++) {
            for (int y = 0; y < image.getHeight(); y++) {
                // Find non-black pixels
                if (imageArray[y][x][0] != 0) {
                    addPoint(x, y);
                }
            }
        }
    }

    /**
     * Adds a single point to the hough transform. You can use this method directly
     * if your data isn't represented as a buffered image.
     */
    public void addPoint(int x, int y) {

        // Go through each value of theta
        for (int t = 0; t < maxTheta; t++) {

            //Work out the r values for each theta step
            int r = (int) (((x - centerX) * cosCache[t]) + ((y - centerY) * sinCache[t]));

            // this copes with negative values of r
            r += houghHeight;

            if (r < 0 || r >= doubleHeight) continue;

            // Increment the hough array
            houghArray[t][r]++;
        }

        numPoints++;
    }

    public List<HoughLine> getLines(int n) {
        return(getLines(n, threshold));
    }

    /**
     * Once points have been added in some way this method extracts the lines and returns them as a Vector
     * of HoughLine objects, which can be used to draw on the
     *
     * @param threshold The percentage threshold above which lines are determined from the hough array
     */
    public List<HoughLine> getLines(int n, int threshold) {

        // Initialise the vector of lines that we'll return
        Vector<HoughLine> lines = new Vector<>(20);

        // Only proceed if the hough array is not empty
        if (numPoints == 0) return lines;

        // Search for local peaks above threshold to draw
        for (int t = 0; t < maxTheta; t++) {
            loop:
            for (int r = neighbourhoodSize; r < doubleHeight - neighbourhoodSize; r++) {

                // Only consider points above threshold
                if (houghArray[t][r] > threshold) {

                    int peak = houghArray[t][r];

                    // Check that this peak is indeed the local maxima
                    for (int dx = -neighbourhoodSize; dx <= neighbourhoodSize; dx++) {
                        for (int dy = -neighbourhoodSize; dy <= neighbourhoodSize; dy++) {
                            int dt = t + dx;
                            int dr = r + dy;
                            if (dt < 0) dt = dt + maxTheta;
                            else if (dt >= maxTheta) dt = dt - maxTheta;
                            if (houghArray[dt][dr] > peak) {
                                // found a bigger point nearby, skip
                                continue loop;
                            }
                        }
                    }

                    // calculate the true value of theta
                    double theta = t * thetaStep;

                    // add the line to the vector
                    lines.add(new HoughLine(theta, r, width, height, houghArray[t][r]));
                }
            }
        }

        lines.sort(Collections.reverseOrder());
        lines.setSize(n);

        return lines;
    }

    @Override
    public Image transformSequential(Image image) {
        addPoints(image);
        List<HoughLine> lines = getLines(noLines);
        for(int x=0;x<image.getWidth();x++)
            for(int y=0;y<image.getHeight();y++) {
                result[y][x][0] = drawLines(x, y, lines);
            }
        return new Image(result);
    }

    private int drawLines(int x, int y, List<HoughLine> lines){
        int rez = 0;
        if(imageArray[y][x][0] != 0)
            rez = 128;
        for (HoughLine line : lines) {
            if(Objects.isNull(line))
                break;
            double x1 = line.getX1();
            double x2 = line.getX2();
            double y1 = line.getY1();
            double y2 = line.getY2();
            double val = (y-y1)/(y2-y1) - (x-x1)/(x2-x1);
            double lineThreshold = 0.005;
            if (-lineThreshold <= val && val <= lineThreshold) {
                 return 255;
            }
        }
        return rez;
    }

    @Override
    public Image transformParallel(Image image) {
        Entry[][] tasks = Main.splitTasks(image.getWidth(), image.getHeight(), Settings.processes-1);
        sendTasks(tasks);
        List<Integer[][]> partialHoughArrays = new LinkedList<>();
        for(int i=1;i<Settings.processes;i++){
            int[] partialPoints = new int[1];
            MPI.COMM_WORLD.Recv(partialPoints, 0, 1 , MPI.INT, i, 0);
            Integer[][] partialHoughArray = receiveArray(i, Integer[][]::new);
            numPoints += partialPoints[0];
            partialHoughArrays.add(partialHoughArray);
        }
        for(int t=0;t<maxTheta;t++)
            for(int d=0;d<doubleHeight;d++){
                for(Integer[][] partialHoughArray: partialHoughArrays)
                    houghArray[t][d] += partialHoughArray[t][d];
            }

        List<HoughLine> lines = getLines(noLines);

        for(int i=1;i<Settings.processes;i++)
            sendArray(lines.toArray(), i);
        for(int i=1;i<Settings.processes;i++){
            Integer[] results = receiveArray(i, Integer[]::new);
            for(int r=0;r<results.length;r++){
                Entry e = tasks[i-1][r];
                result[e.getY()][e.getX()][0] = results[r];
            }
        }
        return new Image(result);
    }

    @Override
    public void worker(Image image) {
        Entry[] tasks = receiveTasks();
        for(Entry entry: tasks){
            if(imageArray[entry.getY()][entry.getX()][0] != 0)
                addPoint(entry.getX(), entry.getY());
        }
        MPI.COMM_WORLD.Send(new int[]{numPoints}, 0, 1, MPI.INT, 0, 0);
        sendArray(houghArray, 0);
        HoughLine[] lines = receiveArray(0, HoughLine[]::new);
        Integer[] results = new Integer[tasks.length];
        for(int i=0;i<tasks.length;i++)
            results[i] = drawLines(tasks[i].getX(), tasks[i].getY(), Arrays.asList(lines));
        sendArray(results, 0);
    }
}

