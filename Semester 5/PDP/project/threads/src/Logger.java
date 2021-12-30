import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
    public static void log(double time, int width, int height, String transformer){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("data/logs.csv", true)))){
            writer.println(
                    time + ","
                    + Settings.threads + ","
                    + transformer + "Regular,"
                    + width + ","
                    + height
            );
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
