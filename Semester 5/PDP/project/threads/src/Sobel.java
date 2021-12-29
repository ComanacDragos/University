public class Sobel implements Transformer{
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
    public Image transform(Image image) {
        if(image.getChannels() != 1)
            throw new RuntimeException("Image must be grayscale");

        Image gx = sobelV.transform(image);
        Image gy = sobelH.transform(image);
        int[][][] result = new int[image.getHeight()][image.getWidth()][1];
        for(int i=0;i<image.getHeight();i++)
            for(int j=0;j<image.getWidth();j++){
                int s1 = gx.getImageArray()[i][j][0];
                int s2 = gy.getImageArray()[i][j][0];
                double gradient = Math.sqrt(Math.pow(s1, 2)+Math.pow(s2, 2));
                if(gradient > threshold){
                    result[i][j][0] = 128;//(int)gradient;
                }
            }
        return new Image(result);
    }
}
