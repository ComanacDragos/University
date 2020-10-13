public class Animal {
    String name;
    static int existent_animals = 0;

    public Animal(String name)
    {
        this.name = name;
        Animal.existent_animals += 1;
    }

    @Override
    public String toString()
    {
        return "Information: \n\t" + this.name;
    }

    public static int getExistent_animals()
    {
        return Animal.existent_animals;
    }
}
