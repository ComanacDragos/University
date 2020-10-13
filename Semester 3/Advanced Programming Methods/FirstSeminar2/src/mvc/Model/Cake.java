package mvc.Model;


public class Cake implements Model {
    int radius;
    String name;

    public Cake(int radius, String name)
    {
        this.radius = radius;
        this.name = name;
    }

    @Override
    public int getWeight() {
        return 50 * this.radius;
    }

    @Override
    public String toString() {
        return this.name + " " + this.getWeight();
    }
}
