import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
    public static void log(double time, int threads, String variant, int p1Degree, int p2Degree){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("data/logs.csv", true)))){
            writer.print(time + ","
                    + threads + ","
                    + variant + ","
                    + p1Degree + ","
                    + p2Degree
                    + "\n"
            );
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
