public class SmallPizza implements Pizza{
    @Override
    public int getPrice() {
        return 5;
    }

    @Override
    public int getWeight() {
        return 200;
    }

    @Override
    public String getName() {
        return "Small pizza";
    }

}
