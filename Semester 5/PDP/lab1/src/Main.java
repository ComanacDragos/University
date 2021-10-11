import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;

public class Main {
    public static void main(String[] args) {
        double totalTime = 0.0;
        long actualTime = System.currentTimeMillis();
        for(int i=0;i<Settings.noIterations;i++)
            totalTime += oneIteration();
        double averageTime = totalTime / (Settings.noIterations * Settings.numberOfThreads);
        actualTime = System.currentTimeMillis() - actualTime;
        Main.documentResults(averageTime, actualTime);
        System.out.println("Average time per thread: " + averageTime + "ms " +
                "--- Total time of all threads: " + totalTime + "ms " +
                "--- Actual time: " + actualTime + "ms");
    }

    //Time per thread,Total time,Number of threads,Number of products,Number of products per thread,Granularity,MoneyLock,Number of iterations
    public static void documentResults(double averageTimePerThread, double actualTotalTime){
        try (PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter("data.csv", true)))) {
            writer.println(averageTimePerThread + ","
                            + actualTotalTime + ","
                            + Settings.numberOfThreads + ","
                            + Settings.numberOfProducts + ","
                            + Settings.numberOfProductsPerThread + ","
                            + Settings.granularity + ","
                            + Settings.moneyLock + ","
                            + Settings.noIterations
            );
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static long oneIteration(){
        Inventory inventory = new Inventory(Settings.numberOfProducts);
        AtomicLong totalTime = new AtomicLong(0);
        AtomicBoolean isFinished = new AtomicBoolean(false);

        if (Settings.printProductsAtTheStart) {
            inventory.getAvailableProducts().forEach(System.out::println);
            System.out.println();
        }

        List<BuyerThread> buyerThreads = new LinkedList<>();
        CheckerThread checkerThread = new CheckerThread(inventory, isFinished);

        for(int i = 0; i<Settings.numberOfThreads; i++){
            BuyerThread thread = new BuyerThread(inventory, totalTime);
            buyerThreads.add(thread);
            thread.start();
        }
        checkerThread.start();
        buyerThreads.forEach(
                thread -> {
                    try {
                        thread.join();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
        );
        //System.out.println();
        //System.out.println("Total time: " + totalTime.get() + "ms");
        isFinished.set(true);
        try {
            checkerThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        inventory.inventoryCheck("main");
        //System.out.println("Money: " + inventory.getAmountOfMoney());

        if(Settings.printProductsAtTheEnd)
            inventory.getAvailableProducts().forEach(System.out::println);

        return totalTime.get();
    }
}
