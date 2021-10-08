import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.locks.ReentrantLock;

public class Inventory {
    public static Logger logger = new Logger("Inventory");
    public static Random rand = Product.rand;

    public Integer amountOfMoney = 0;
    private final List<Bill> bills = new Vector<>(); // thread safe
    private final List<Product> availableProducts = new LinkedList<>();

    private final Map<Integer, ReentrantLock> lockMap = new ConcurrentHashMap<>();

    public Inventory(Integer numberOfProducts){
        while(availableProducts.size() != numberOfProducts){
            Product product = new Product();
            availableProducts.add(product);
            lockMap.put(product.getId(), new ReentrantLock());
        }
    }

    public Product getProduct(){
        Product product = availableProducts.get(rand.nextInt(availableProducts.size()));
        lockMap.get(product.getId()).lock();
        return product;
    }

    public void releaseProduct(Integer productId){
        lockMap.get(productId).unlock();
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
        amountOfMoney += bill.getValue();
    }

    public void inventoryCheck(){
        Integer totalSum = bills.stream()
                .map(Bill::getValue)
                .reduce(0, Integer::sum);
        if(!totalSum.equals(amountOfMoney)){
            logger.log("check failed: Inventory sum: " + amountOfMoney + " Computed sum: " + totalSum);
        }
        else{
            logger.log("check successful");
        }
    }
}
