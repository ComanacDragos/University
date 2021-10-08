import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;

public class Main {
    public static void main(String[] args) {
        double totalTime = 0.0;
        for(int i=0;i<Settings.noIterations;i++)
            totalTime += oneIteration();
        double averageTime = totalTime / Settings.noIterations;
        System.out.println("Average time: " + averageTime + "ms --- Total time: " + totalTime + "ms");
    }

    public static long oneIteration(){
        Inventory inventory = new Inventory(Settings.numberOfProducts);
        AtomicLong totalTime = new AtomicLong(0);

        if (Settings.printProductsAtTheStart) {
            inventory.getAvailableProducts().forEach(System.out::println);
            System.out.println();
        }

        List<BuyerThread> buyerThreads = new LinkedList<>();

        for(int i = 0; i<Settings.numberOfThreads; i++){
            BuyerThread thread = new BuyerThread(inventory, totalTime);
            buyerThreads.add(thread);
            thread.start();
        }
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
        inventory.inventoryCheck();
        //System.out.println("Money: " + inventory.getAmountOfMoney());

        if(Settings.printProductsAtTheEnd)
            inventory.getAvailableProducts().forEach(System.out::println);

        return totalTime.get();
    }
}
