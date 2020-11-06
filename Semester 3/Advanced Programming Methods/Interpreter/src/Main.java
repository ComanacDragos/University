import Controller.Controller;
import Repository.IRepository;
import Repository.Repository;
import  View.View;

public class Main {
    public static void main(String[] args) {
        IRepository repository = new Repository("src/Files/log.txt");
        Controller controller = new Controller(repository);
        controller.setPrintFlag(true);
        View view = new View(controller);
        view.start();
    }
}