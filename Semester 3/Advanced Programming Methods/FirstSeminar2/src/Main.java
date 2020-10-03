import mvc.*;

public class Main {
    public static void main(String[] args) {
        Repository repo = new Repository();
        repo.store(new Apple(20, "Apple1"));
        repo.store(new Book(50, "Book1"));
        repo.store(new Cake(20, "Cake1"));
        repo.store(new Apple(5, "Apple2"));
        repo.store(new Book(20, "Book2"));
        repo.store(new Cake(2, "Cake2"));

        Controller controller = new Controller(repo);

        View view = new View(controller);

        view.start();
    }
}

