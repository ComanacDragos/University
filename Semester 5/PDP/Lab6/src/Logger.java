import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
    public static void log(double time, int threads, int vertices, int edges){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("data/logs.csv", true)))){
            writer.print(time + ","
                    + threads + ","
                    + vertices + ","
                    + edges
                    + "\n"
            );
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
