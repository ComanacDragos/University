public class Penguin extends Animal{
    int height, weight;

    Penguin(String name, int height, int weight) throws MyException
    {
        super(name);

        if(height <= 0 || weight <= 0 ) {
            Animal.existent_animals -= 1;
            throw new MyException("Bad numbers");
        }

        this.height = height;
        this.weight = weight;
    }

    @Override
    public String toString() {
        return super.toString() + "\n\t\t Weight: " + Integer.toString(this.weight) + "\n\t\t Height: " + Integer.toString(this.height);
    }
}
