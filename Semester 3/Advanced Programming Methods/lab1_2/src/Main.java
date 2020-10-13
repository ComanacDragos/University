public class Main {
    public static void main(String[] args) {
        Animal a1 = new Animal("bert");

        System.out.println(a1);

        try {
            Animal a2 = new Penguin("bert2", 5, 15);
            System.out.println(a2);
        }
        catch (MyException e) {
            System.out.println(e.getMessage());
        }

        try {
            Animal a3 = new Penguin("bert3", 0, 15);
            System.out.println(a3);
        }
        catch (MyException e) {
            System.out.println(e.getMessage());
        }

        System.out.print("Existent animals are: ");
        System.out.println(Animal.getExistent_animals());
    }
}
