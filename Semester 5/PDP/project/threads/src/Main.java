import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        int[][][] a = new int[][][]{{
                {}
        }};

        double[][] filter = new double[][]{
                {1., 2., 1.},
                {0., 0., 0.},
                {-1., -2., -1.},
        };

        Convolution testC = new Convolution(filter);
        GaussianBlur gaussianBlur = new GaussianBlur();
        GrayScale grayScale = new GrayScale();
        Sobel sobel = new Sobel(150);
        Hough hough = new Hough(100, 10);

        Image img = new Image("E:\\University\\Semester 5\\PDP\\project\\threads\\data\\cameraman.jpg");
        //new DisplayImage(img);
        img = grayScale.transform(img);
        //new DisplayImage(img);
        //img = gaussianBlur.transform(img);
        new DisplayImage(img);
        img = sobel.transform(img);
        new DisplayImage(img);
        img = hough.transform(img);
        new DisplayImage(img);
    }
}
