public class ConvolutionSequential implements Transformer{
    double[][] filter;

    public ConvolutionSequential(double[][] filter) {
        this.filter = filter;
    }

    @Override
    public Image transform(Image image) {
        int[][][] imageArray = image.getImageArray();
        int[][][] result = new int[image.getHeight()][image.getWidth()][3];
        for(int y=0;y<image.getHeight();y++)
            for(int x=0;x<image.getWidth();x++)
            for(int c=0;c<image.getChannels();c++){
                int sum = 0;
                int halfFilter = filter.length/2;
                for(int fy=-halfFilter;fy<halfFilter;fy++)
                    for(int fx=-halfFilter;fx<halfFilter;fx++){
                        int valueFromImage;
                        if(x+fx<0 || x+fx>=image.getWidth() || y+fy<0 || y+fy>=image.getHeight())
                            valueFromImage = 0;
                        else
                            valueFromImage = imageArray[y+fy][x+fx][c];
                        sum += valueFromImage * filter[fy+halfFilter][fx+halfFilter];
                    }
                result[y][x][c] = sum;
            }
        return new Image(result);
    }
}
