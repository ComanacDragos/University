public class Solver implements Transformer{
    GaussianBlur gaussianBlur = new GaussianBlur();
    GrayScale grayScale = new GrayScale();
    Sobel sobel = new Sobel(150);
    Hough hough = new Hough(100, 10);

    @Override
    public Image transformSequential(Image image) {
        Image img = image;
        if(Settings.displayImage)
            new DisplayImage(img);
        long start = System.currentTimeMillis();
        img = grayScale.transform(img);
        System.out.println("Grayscale: " + (System.currentTimeMillis() - start));
        if(Settings.displayImage)
            new DisplayImage(img);

        start = System.currentTimeMillis();
        img = gaussianBlur.transform(img);
        System.out.println("GaussBlur: " + (System.currentTimeMillis() - start));
        if(Settings.displayImage)
            new DisplayImage(img);

        start = System.currentTimeMillis();
        img = sobel.transform(img);
        System.out.println("Sobel: " + (System.currentTimeMillis() - start));
        if(Settings.displayImage)
            new DisplayImage(img);

        start = System.currentTimeMillis();
        img = hough.transform(img);
        System.out.println("Hough: " + (System.currentTimeMillis() - start));
        if(Settings.displayImage)
            new DisplayImage(img);
        return img;
    }

    @Override
    public Image transformParallel(Image image) {
        return transformSequential(image);
    }
}
