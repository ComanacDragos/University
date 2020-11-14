package View.ConsoleUserInterface;

import Controller.Controller;
import Exceptions.MyException;


public class RunExample extends Command{
    Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try{
            this.controller.executeAllSteps();
            System.out.println("Program completed");
        }
        catch (MyException exception){
            System.out.println(exception.getMessage());
        }
    }
}
