public interface Transformer {
    default Image transform(Image image){
        initialise(image);
        if(Settings.threads == 1)
            return transformSequential(image);
        return transformParallel(image);
    }
    Image transformSequential(Image image);
    Image transformParallel(Image image);
    default void initialise(Image image){}
}
