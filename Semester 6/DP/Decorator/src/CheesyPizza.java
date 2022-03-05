public class CheesyPizza extends DecoratedPizza{
    Cheese cheese;

    public CheesyPizza(Pizza component, Cheese cheese) {
        super(component);
        this.cheese = cheese;
    }

    @Override
    public int getWeight() {
        return super.getWeight() + 50;
    }

    @Override
    public String getName() {
        String type = switch (cheese){
            case GORGONZOLA -> "gorgonzola";
            case BRIE -> "brie";
            case CHEDDAR -> "cheddar";
        };
        return super.getName() + " with " + type + " cheese";
    }
}
