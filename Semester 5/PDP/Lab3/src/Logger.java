import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
    public static void log(double time){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("data/logs.csv", true)))){
            writer.print(time + ","
                    + Settings.tasks + ","
                    + Settings.threadPoolSize + ","
                    + Settings.al + ","
                    + Settings.ac + ","
                    + Settings.bl + ","
                    + Settings.bc + "\n"
            );
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
