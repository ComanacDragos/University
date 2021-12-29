import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
    public static void log(double time, int width, int height){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("data/logs.csv", true)))){
            writer.print(time + ","
                    + Settings.threads + ","
                    + width + ","
                    + height + ","
            );
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
