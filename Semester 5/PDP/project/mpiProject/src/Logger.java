import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Logger {
    public static void log(double time, int width, int height, String transformer){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("E:\\University\\Semester 5\\PDP\\project\\mpiProject\\data\\logs.csv", true)))){
            writer.println(
                    time + ","
                    + Settings.processes + ","
                    + transformer + "MPI,"
                    + width + ","
                    + height
            );
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public static void logToConsole(Object obj){
        System.out.println(Main.rank + ". " + obj.toString());
    }
}
