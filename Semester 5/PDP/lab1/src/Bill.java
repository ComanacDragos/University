import java.util.HashMap;
import java.util.Map;

public class Bill {
    public Logger logger = new Logger("Bill");

    private final Map<Product, Integer> productToQuantitySold = new HashMap<>();
    private Integer value=0;

    public Bill(long owner){
        logger.setContext("Bill for " + owner);
    }

    public void addProduct(Product product, Integer quantity){
        if(productToQuantitySold.containsKey(product)){
            Integer newQuantity = productToQuantitySold.get(product) + quantity;
            productToQuantitySold.put(product, newQuantity);
        }else{
            productToQuantitySold.put(product, quantity);
        }
        value += quantity * product.getUnitPrice();
        if(Settings.logBill){
            logger.log("added " + product.getId()
                    + " quantity: " + quantity + "/" + product.getQuantity() + " price: " + product.getUnitPrice());
        }
    }

    public Integer getValue() {
        return value;
    }

    public Map<Product, Integer> getProductToQuantitySold() {
        return productToQuantitySold;
    }
}
