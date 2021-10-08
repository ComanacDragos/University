import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Inventory {
    public static Logger logger = new Logger("Inventory");
    public static Random rand = Product.rand;

    public Integer amountOfMoney = 0;
    private final List<Bill> bills = new Vector<>(); // thread safe
    private final List<Product> availableProducts = new LinkedList<>();
    private final Map<Integer, Integer> initialQuantities = new HashMap<>();

    private final Map<Integer, Semaphore> lockMap = new ConcurrentHashMap<>();
    private final Semaphore globalLock = new Semaphore(1);
    private final Semaphore moneyLock = new Semaphore(1);
    private final ReadWriteLock inventoryCheckLock = new ReentrantReadWriteLock();

    /*
     lockMap
        - for PRODUCT mode
        - locks for each product
        - each product is locked while it is processed
     globalLock
        - for INVENTORY mode
        - locks all products while a single product is processed

     moneyLock
         - lock for the total amount of money
         - it is controlled by the moneyLock setting
     inventoryCheckLock
         - read write lock used only for checking the inventory
         - the threads acquire the read lock until they finish processing the bills
         - the inventory check operation acquires the write lock
         - this is used so that the threads don't modify the state while the inventory check is performed
     */

    public Inventory(Integer numberOfProducts){
        while(availableProducts.size() != numberOfProducts){
            Product product = new Product();
            availableProducts.add(product);
            initialQuantities.put(product.getId(), product.getQuantity());
            lockMap.put(product.getId(), new Semaphore(1));
        }
    }

    public void lockInventory(){
        try{
            globalLock.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void releaseInventory(){
        globalLock.release();
    }

    public void lockCheck(){
        this.inventoryCheckLock.readLock().lock();
    }

    public void unlockCheck(){
        this.inventoryCheckLock.readLock().unlock();
    }

    public Product getProduct(){
        Product product = availableProducts.get(rand.nextInt(availableProducts.size()));
        try{
            switch (Settings.granularity){
                case PRODUCT -> lockMap.get(product.getId()).acquire();
                case INVENTORY -> lockInventory();
                default -> {}
            }
        } catch (InterruptedException e) {
        e.printStackTrace();
        }
        return product;
    }

    public void releaseProduct(Integer productId){
        switch (Settings.granularity){
            case PRODUCT -> lockMap.get(productId).release();
            case INVENTORY -> releaseInventory();
            default -> {}
        }
    }

    public List<Product> getAvailableProducts() {
        return availableProducts;
    }

    public Integer inventorySize(){
        return availableProducts.size();
    }

    public Integer getAmountOfMoney() {
        return amountOfMoney;
    }

    public void addBill(Bill bill){
        bills.add(bill);
        if(Settings.moneyLock){
            try{
                moneyLock.acquire();
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
        amountOfMoney += bill.getValue();
        if(Settings.moneyLock){
            moneyLock.release();
        }
    }

    public void inventoryCheck(String context){
        this.inventoryCheckLock.writeLock().lock();
        Integer totalSum = bills.stream()
                .map(Bill::getValue)
                .reduce(0, Integer::sum);
        if(!totalSum.equals(amountOfMoney)){
            logger.log(context + " money check failed: Inventory sum: " + amountOfMoney + " Computed sum: " + totalSum);
        }

        Map<Integer, Integer> productIdToQuantity = new HashMap<>();
        availableProducts.forEach(product -> productIdToQuantity.put(product.getId(), 0));
        bills.forEach(bill -> bill.getProductToQuantitySold().entrySet().forEach(
                entry -> {
                    if(productIdToQuantity.containsKey(entry.getKey().getId())){
                        int quantity = productIdToQuantity.get(entry.getKey().getId()) + entry.getValue();
                        productIdToQuantity.put(entry.getKey().getId(), quantity);
                    }else{
                        productIdToQuantity.put(entry.getKey().getId(), entry.getValue());
                    }

                }
        ));

        //productIdToQuantity.entrySet().forEach(entry -> System.out.println(entry.getKey() + " --> " + entry.getValue()));
        int quantityErrors = (int) availableProducts.stream()
                .filter(product -> {
                    Integer quantity = initialQuantities.get(product.getId()) - product.getQuantity();
//                    if(product.getQuantity() < 0){
//                        logger.log(product.getQuantity().toString());
//                    }
//
//                    if(!quantity.equals(productIdToQuantity.get(product.getId()))){
//                        logger.log(product.getId().toString() + " " + quantity + " " + productIdToQuantity.get(product.getId()));
//                    }
                    return product.getQuantity() < 0 || !quantity.equals(productIdToQuantity.get(product.getId()));
                })
                .count();
        if(quantityErrors != 0){
            logger.log(context + " quantity check failed with " + quantityErrors + " errors");
        }
        this.inventoryCheckLock.writeLock().unlock();
    }
}
