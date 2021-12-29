import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Vector;

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
    protected int[][] houghArray;

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

    int threshold, noLines;

    public Hough(int threshold, int noLines){
        this.threshold = threshold;
        this.noLines = noLines;
    }

    public void initialise(int width, int height) {
        this.width = width;
        this.height = height;

        // Calculate the maximum height the hough array needs to have
        houghHeight = (int) (Math.sqrt(2) * Math.max(height, width)) / 2;

        // Double the height of the hough array to cope with negative r values
        doubleHeight = 2 * houghHeight;

        // Create the hough array
        houghArray = new int[maxTheta][doubleHeight];

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
                if (image.getImageArray()[y][x][0] != 0) {
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
    public Image transform(Image image) {
        if(image.getChannels()!=1)
            throw new RuntimeException("Image must be grayscale");
        initialise(image.getWidth(), image.getHeight());
        addPoints(image);
        List<HoughLine> lines= getLines(noLines);
        lines.forEach(System.out::println);
        int[][][] result = new int[image.getHeight()][image.getWidth()][1];
        for(int y=0;y<image.getHeight();y++)
            for(int x=0;x<image.getWidth();x++) {
                if(image.getImageArray()[y][x][0] != 0)
                    result[y][x][0] = 128;
                for (HoughLine line : lines) {
                    double x1 = line.getX1();
                    double x2 = line.getX2();
                    double y1 = line.getY1();
                    double y2 = line.getY2();
                    double val = (y-y1)/(y2-y1) - (x-x1)/(x2-x1);
                    double lineThreshold = 0.005;
                    if (-lineThreshold <= val && val <= lineThreshold) {
                        result[y][x][0] = 255;
                        break;
                    }
                }
            }

        return new Image(result);
    }
}

