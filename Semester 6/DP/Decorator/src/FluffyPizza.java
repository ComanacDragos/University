public class FluffyPizza extends DecoratedPizza{

    public FluffyPizza(Pizza component) {
        super(component);
    }

    @Override
    public int getPrice() {
        return super.getPrice() + 5;
    }

    @Override
    public String getName() {
        return super.getName() + " fluffy";
    }
}
