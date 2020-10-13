package View;

import Controller.Controller;
import Exceptions.MyException;
import Model.GeometricObject;

import java.util.Scanner;

public class View {
    Controller controller;
    Scanner console;

    public View(Controller controller){
        this.controller = controller;
        this.console = new Scanner(System.in);
    }

    void printMenu(){
        System.out.println("1.Store\n2.Get objects with volume at least 25cm3\n3.List\n4.Exit\n");
    }

    public void start(){
        while(true){
            this.printMenu();
            System.out.print(">> ");

            int choice = this.console.nextInt();
            this.console.nextLine();

            if(choice == 1)
                this.store();
            else if(choice == 2)
                this.getObjectsWithVolume();
            else if(choice == 3)
                this.list();
            else if(choice == 4)
                return;

        }
    }

    void store(){
        System.out.print("type dimension1 [dimension2] name\n>> ");
        String[] tokens = this.console.nextLine().split(" ");

        try {
            if (tokens[0].matches("^cube"))
                this.controller.storeCube(Double.parseDouble(tokens[1]), tokens[2]);
            else if(tokens[0].matches("^sphere"))
                this.controller.storeSphere(Double.parseDouble(tokens[1]), tokens[2]);
            else if(tokens[0].matches("^cylinder"))
                this.controller.storeCylinder(Double.parseDouble(tokens[1]), Double.parseDouble(tokens[2]), tokens[3]);
            System.out.println("Item stored successfully");
        }
        catch (MyException exc){
            System.out.println(exc.getMessage());
        }
    }

    void getObjectsWithVolume(){
        try {
            for (GeometricObject item : this.controller.getObjects(25))
                System.out.println(item);
        }
        catch (MyException exc){
            System.out.println(exc.getMessage());
        }
        System.out.println();
    }

    void list(){
        for(GeometricObject item : this.controller.getAll())
            System.out.println(item);
        System.out.println();
    }
}
