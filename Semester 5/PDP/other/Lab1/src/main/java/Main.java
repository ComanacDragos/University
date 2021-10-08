import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Inventory inventory = new Inventory(Settings.number_of_products);

        inventory.getAvailableProducts().forEach(System.out::println);
        System.out.println();

        List<BuyerThread> buyerThreads = new LinkedList<>();

        for(int i=0;i<Settings.number_of_threads;i++){
            BuyerThread thread = new BuyerThread(inventory);
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
        System.out.println();
        inventory.inventoryCheck();
        System.out.println("Money: " + inventory.getAmountOfMoney());
        inventory.getAvailableProducts().forEach(System.out::println);
    }
}
