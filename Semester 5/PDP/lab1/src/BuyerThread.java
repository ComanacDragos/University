import java.util.Random;
import java.util.concurrent.atomic.AtomicLong;

public class BuyerThread extends Thread{
    public Logger logger = new Logger("Thread");

    public static Random rand = Product.rand;
    Integer number_of_products;

    Inventory inventory;
    AtomicLong totalTime;

    public BuyerThread(Inventory inventory, AtomicLong totalTime){
        this.inventory = inventory;
        this.number_of_products = Settings.numberOfProductsPerThread;
        this.totalTime = totalTime;
    }

    @Override
    public void run(){
        logger.setContext(logger.getContext() + " " + Thread.currentThread().getId());
        if(Settings.printThreadInfo)
            logger.log("start with " + number_of_products + " products to buy");

        Bill bill = new Bill(Thread.currentThread().getId());
        int remainingProducts = number_of_products;

        long startTime = System.currentTimeMillis();
        while (number_of_products!=0){
            Product product = inventory.getProduct();
            if(product.getQuantity() > 0){
                Integer quantity = rand.nextInt(product.getQuantity()) + 1;
                bill.addProduct(product, quantity);
                product.setQuantity(product.getQuantity() - quantity);
                remainingProducts--;
            }
            inventory.releaseProduct(product.getId());
            number_of_products--;
        }
        inventory.addBill(bill);
        long totalTime = (System.currentTimeMillis() - startTime);
        this.totalTime.getAndAdd(totalTime);

        if(Settings.printThreadInfo)
            logger.log("end " + remainingProducts + " remaining products to buy; done in: " + totalTime + "ms");
    }
}
