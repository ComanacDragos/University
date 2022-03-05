public class LargePizza implements Pizza{
    @Override
    public int getPrice() {
        return 10;
    }

    @Override
    public int getWeight() {
        return 500;
    }

    @Override
    public String getName() {
        return "Large pizza";
    }
}
