public class DecoratedPizza implements Pizza{
    private final Pizza component;

    public DecoratedPizza(Pizza component){
        this.component = component;
    }

    @Override
    public int getPrice() {
        return component.getPrice();
    }

    @Override
    public int getWeight() {
        return component.getWeight();
    }

    @Override
    public String getName() {
        return component.getName();
    }
}
