import java.util.Random;

public class Product {
    static Integer globalProductId =0;
    public static Random rand = new Random();

    private final Integer id;
    private final Integer unitPrice;
    private Integer quantity;

    public Product(){
        Product.globalProductId++;
        this.id = Product.globalProductId;
        this.unitPrice = Product.rand.nextInt(10) + 1;
        this.quantity = Product.rand.nextInt(100) + 1;
    }

    public Integer getUnitPrice() {
        return unitPrice;
    }

    public Integer getQuantity() {
        return quantity;
    }

    public void setQuantity(Integer quantity) {
        this.quantity = quantity;
    }

    public Integer getId() {
        return id;
    }

    @Override
    public String toString() {
        return "Product{" +
                "id=" + id +
                ", unitPrice=" + unitPrice +
                ", quantity=" + quantity +
                '}';
    }
}
