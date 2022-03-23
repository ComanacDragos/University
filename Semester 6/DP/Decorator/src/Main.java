public class Main {
    public static Pizza smallPizza(){
        return new SmallPizza();
    }

    public static Pizza smallPizzaWithPeperoni(int quantity){
        return new PepperoniPizza(new SmallPizza(), quantity);
    }

    public static Pizza largeFluffyPizzaWithCheeseWithPepperoni(int quantity, Cheese cheese){
        return new PepperoniPizza(
                new CheesyPizza(
                        new FluffyPizza(
                                new LargePizza()
                        ),
                        cheese
                ),
                quantity
        );
    }

    public static Pizza pizzaWithEverything(){
        return new PepperoniPizza(
                new CheesyPizza(
                        new CheesyPizza(
                            new CheesyPizza(
                                    new FluffyPizza(
                                            new LargePizza()
                                    ),
                                    Cheese.BRIE
                            ),
                                Cheese.GORGONZOLA
                        ),
                        Cheese.CHEDDAR
                ),
                10
        );
    }


    public static void displayPizza(Pizza pizza){
        System.out.println(pizza.getName());
        System.out.println("\tWeight: " + pizza.getWeight());
        System.out.println("\tPrice: " + pizza.getPrice());
    }

    public static void main(String[] args) {
        displayPizza(smallPizza());
        System.out.println("\n");
        displayPizza(smallPizzaWithPeperoni(10));
        System.out.println("\n");
        displayPizza(largeFluffyPizzaWithCheeseWithPepperoni(5, Cheese.BRIE));
        System.out.println("\n");
        displayPizza(pizzaWithEverything());
        System.out.println("\n");
    }
}
