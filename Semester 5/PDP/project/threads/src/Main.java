import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        GaussianBlur gaussianBlur = new GaussianBlur();
        for(int i=0;i<3;i++){
            System.out.println(Arrays.toString(gaussianBlur.filter[i]));
        }
        Image img = new Image("E:\\University\\Semester 5\\PDP\\project\\threads\\data\\engine.png");
        new DisplayImage(img);
    }
}
