import java.util.LinkedList;
import java.util.List;

public class Solver implements Transformer{
    List<Transformer> transformers = new LinkedList<>(){{
        add(new GrayScale());
        add(new GaussianBlur());
        add(new Sobel(150));
        add(new Hough(100, 10));
    }};

    @Override
    public Image transformSequential(Image image) {
        Image img = image;
        if(Settings.debugMode)
            new DisplayImage(img);
        for(Transformer transformer: transformers)
            img = applyTransform(transformer, img);
        return img;
    }

    private Image applyTransform(Transformer transformer, Image image){
        long start = System.currentTimeMillis();
        Image result = transformer.transform(image);
        if(Settings.debugMode)
            new DisplayImage(result);
        else
            Logger.log(System.currentTimeMillis()-start, image.getWidth(), image.getHeight(), transformer.toString().split("@")[0]);
        return result;
    }

    @Override
    public Image transformParallel(Image image) {
        return transformSequential(image);
    }
}
