package View.ConsoleUserInterface;

import Controller.Controller;
import Exceptions.MyException;
import Model.ADTs.MyDictionary;


public class RunExample extends Command{
    Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try{
            this.controller.getRepository()
                    .getPrograms()
                    .get(0)
                    .getExecutionStack()
                    .peek()
                    .typeCheck(new MyDictionary<>());

            this.controller.executeAllSteps();
            System.out.println("Program completed");
        }
        catch (MyException exception){
            System.out.println(exception.getMessage());
        }
    }
}
