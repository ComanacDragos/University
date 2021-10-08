import java.util.Random;

public class BuyerThread extends Thread{
    public Logger logger = new Logger("Thread");

    public static Random rand = Product.rand;
    Integer number_of_products;

    Inventory inventory;

    public BuyerThread(Inventory inventory){
        this.inventory = inventory;
        this.number_of_products = rand.nextInt(inventory.inventorySize()) + 1;
    }

    @Override
    public void run(){
        logger.setContext(logger.getContext() + " " + Thread.currentThread().getId());
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
        logger.log("end " + remainingProducts + " remaining products to buy; done in: " + totalTime + "ms");
    }
}
