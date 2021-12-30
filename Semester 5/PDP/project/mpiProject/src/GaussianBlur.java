public class GaussianBlur implements Transformer{
    double[][] filter = new double[][]{
            {2/159., 4/159., 5/159., 4/159., 2/159.},
            {4/159., 9/159., 12/159., 9/159., 4/159.},
            {5/159., 12/159., 15/159., 12/159., 5/159.},
            {4/159., 9/159., 12/159., 9/159., 4/159.},
            {2/159., 4/159., 5/159., 4/159., 2/159.}
    };

    Convolution convolution = new Convolution(filter);

    @Override
    public Image transformSequential(Image image) {
        return convolution.transform(image);
    }

    @Override
    public Image transformParallel(Image image) {
        return transformSequential(image);
    }

    @Override
    public void worker(Image image) {
        convolution.transform(image);
    }
}
