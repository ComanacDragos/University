import java.util.LinkedList;
import java.util.List;
import java.util.Set;

public class Main {

    public static void main(String[] args) {
        //Image img = new Image("E:\\University\\Semester 5\\PDP\\project\\threads\\data\\bus.jpg");
        Image img = new Image(3000, 3000, 3);
        System.out.println(img.getWidth() + "  " + img.getHeight());
        GaussianBlur blur = new GaussianBlur();
        GrayScale grayScale = new GrayScale();
        Sobel sobel = new Sobel(150);
        Hough hough = new Hough(100, 10);
        Solver solver = new Solver();
        //solver.transform(img);
        //img = grayScale.transform(img);
        Transformer trans = solver;

        Settings.threads = 4;
        long startP = System.currentTimeMillis();
        trans.transform(img);
        System.out.println("Parallel: " + (System.currentTimeMillis()-startP));

        Settings.threads = 1;
        long start = System.currentTimeMillis();
        trans.transform(img);
        System.out.println("Seq: " + (System.currentTimeMillis()-start));


    }

    public static List<List<Entry>> splitTasks(Integer w, Integer h){
        int elements = w * h;
        int chunk = elements / Settings.threads;
        int rest = elements % Settings.threads;
        List<List<Entry>> split = new LinkedList<>();
        List<Entry> subSplit = new LinkedList<>();
        for (int j = 0; j < h; j++){
             for (int i = 0; i < w; i++){
                //if(split.size() != Settings.threads) {
                    subSplit.add(new Entry(i, j));
                    if(subSplit.size() == chunk){
                        if(rest > 0){
                            j++;
                            if(j == h)
                                i++;
                            subSplit.add(new Entry(i, j));
                            rest--;
                        }
                        split.add(subSplit);
                        subSplit = new LinkedList<>();
                    }
                //}else {
                //    split.get(--rest).add(new Entry(i, j));
                //}
            }
        }
        return split;
    }
}
