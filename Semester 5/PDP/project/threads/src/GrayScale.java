public class GrayScale implements Transformer{
    @Override
    public Image transform(Image image) {
        if(image.getChannels() == 1)
            return image;

        int[][][] imageArray = image.getImageArray();
        int[][][] result = new int[image.getHeight()][image.getWidth()][1];
        for(int y=0;y<image.getHeight();y++)
            for(int x=0;x<image.getWidth();x++){
                int[] rgb = imageArray[y][x];
                result[y][x][0] = (int) (0.299 * rgb[0] + 0.587 * rgb[1] + 0.114 * rgb[2]);
            }
        return new Image(result);
    }
}
