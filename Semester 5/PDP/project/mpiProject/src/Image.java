import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Random;

public class Image {
    private int height, width, channels;
    private int[][][] imageArray;

    public Image(String path){
        BufferedImage img;
        try {
            img = ImageIO.read(new File(path));
            height = img.getHeight();
            width = img.getWidth();
            if(img.getType() == BufferedImage.TYPE_BYTE_GRAY)
                channels=1;
            else
                channels=3;
            imageArray = new int[height][width][channels];

            int[] aux;
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++) {
                    aux = img.getRaster().getPixel(j, i, new int[channels]);
                    for (int c = 0; c < channels; c++)
                        imageArray[i][j][c] = aux[c];

                }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Image(int[][][] imageArray){
        height = imageArray.length;
        width = imageArray[0].length;
        channels = imageArray[0][0].length;
        this.imageArray = imageArray;
    }

    public Image(int height, int width, int channels){
        this.height = height;
        this.width = width;
        this.channels = channels;
        this.imageArray = new int[height][width][channels];
        Random rand = new Random();
        for(int x=0;x<width;x++)
            for(int y=0;y<height;y++)
                for(int c=0;c<channels;c++)
                    imageArray[y][x][c] = rand.nextInt(256);
    }

    public int getHeight() {
        return height;
    }

    public int getWidth() {
        return width;
    }

    public int[][][] getImageArray() {
        return imageArray;
    }

    public int getChannels() {
        return channels;
    }

    public BufferedImage toBufferedImage(){
        BufferedImage img;
        if(channels == 3)
            img = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        else
            img = new BufferedImage(width, height, BufferedImage.TYPE_BYTE_GRAY);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                img.getRaster().setPixel(j, i, imageArray[i][j]);
        }
        return img;
    }
}
