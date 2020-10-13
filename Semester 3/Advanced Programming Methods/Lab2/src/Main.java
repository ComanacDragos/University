import Controller.Controller;
import Exceptions.MyException;
import Repository.Repository;
import Repository.InMemoryRepository;
import View.View;

public class Main {
    public static void main(String[] args) {
        Repository repository = new InMemoryRepository(50);
        Controller controller = new Controller(repository);

        try {
            controller.storeCube(3, "Cube1");
            controller.storeCube(2, "Cube2");

            controller.storeSphere(3, "Sphere1");
            controller.storeSphere(1, "Sphere2");

            controller.storeCylinder(2,2,"Cylinder1");
            controller.storeCylinder(1,1,"Cylinder2");
        }
        catch (MyException exc){
            System.out.println(exc.getMessage());
        }

        View view = new View(controller);

        view.start();
    }
}
