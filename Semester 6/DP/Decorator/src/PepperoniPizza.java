public class PepperoniPizza extends DecoratedPizza{
    int quantity;

    public PepperoniPizza(Pizza component, int quantity) {
        super(component);
        this.quantity = quantity;
    }

    @Override
    public int getPrice() {
        return super.getPrice() + quantity/2;
    }

    @Override
    public int getWeight() {
        return super.getWeight() + quantity * 2;
    }

    @Override
    public String getName() {
        return super.getName() + " with pepperoni";
    }
}
