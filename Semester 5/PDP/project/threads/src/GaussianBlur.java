
public class GaussianBlur implements Transformer{
    double[][] filter = new double[][]{
            {2/159., 4/159., 5/159., 4/159., 2/159.},
            {4/159., 9/159., 12/159., 9/159., 4/159.},
            {5/159., 12/159., 15/159., 12/159., 5/159.},
            {4/159., 9/159., 12/159., 9/159., 4/159.},
            {2/159., 4/159., 5/159., 4/159., 2/159.}
    };


    @Override
    public Image transform(Image image) {
        return null;
    }
}
