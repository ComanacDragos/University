import java.awt.geom.Line2D;

/*
https://github.com/davidchatting/hough_lines/blob/master/HoughLine.java
 */
public class HoughLine extends Line2D.Float implements Comparable<HoughLine> {
    protected double theta;
    protected double r;
    protected int score;

    /**
     * Initialises the hough line
     */
    public HoughLine(double theta, double r, int width, int height, int score) {
        this.theta = theta;
        this.r = r;
        this.score=score;

        // During processing h_h is doubled so that -ve r values
        int houghHeight = (int) (Math.sqrt(2) * Math.max(height, width)) / 2;

        // Find edge points and vote in array
        float centerX = (float)width / 2;
        float centerY = (float)height / 2;

        // Draw edges in output array
        double tsin = Math.sin(theta);
        double tcos = Math.cos(theta);

        if (theta < Math.PI * 0.25 || theta > Math.PI * 0.75) {
            int x1=0, y1=0;
            int x2=0, y2=height-1;

            x1=(int) ((((r - houghHeight) - ((y1 - centerY) * tsin)) / tcos) + centerX);
            x2=(int) ((((r - houghHeight) - ((y2 - centerY) * tsin)) / tcos) + centerX);

            setLine(x1, y1, x2, y2);
        }
        else {
            int x1=0, y1=0;
            int x2=width-1, y2=0;

            y1=(int) ((((r - houghHeight) - ((x1 - centerX) * tcos)) / tsin) + centerY);
            y2=(int) ((((r - houghHeight) - ((x2 - centerX) * tcos)) / tsin) + centerY);

            setLine(x1, y1, x2, y2);
        }
    }

    @Override
    public String toString() {
        return x1 + ", " + y1 + " - " + x2 + ", " + y2;

    }

    public int compareTo(HoughLine o) {
        return(this.score-o.score);
    }
}
