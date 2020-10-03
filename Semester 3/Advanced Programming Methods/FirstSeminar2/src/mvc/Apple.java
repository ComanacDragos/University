package mvc;

public class Apple implements Model{
    int size;
    String name;

    public Apple(int size, String name)
    {
        this.size = size;
        this.name = name;
    }

    public Apple()
    {
        this.name = "Apple";
        this.size = 1;
    }

    @Override
    public int getWeight() {
        return 10 * size;
    }

    @Override
    public String toString() {
        return this.name;
    }
}
