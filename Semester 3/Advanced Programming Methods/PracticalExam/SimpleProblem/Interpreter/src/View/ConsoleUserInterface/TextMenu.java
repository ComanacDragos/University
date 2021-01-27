package View.ConsoleUserInterface;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class TextMenu {
    private final Map<String, Command> commands;

    public TextMenu(){
        this.commands = new LinkedHashMap<>();
    }

    public void addCommand(Command command){
        this.commands.put(command.getKey(), command);
    }

    private void printMenu(){
        for(Command command : this.commands.values()){
            String line = String.format("%4s : %s", command.getKey(), command.getDescription());
            System.out.println(line);
        }
    }

    public void show(){
        Scanner scanner = new Scanner(System.in);

        while(true){
            this.printMenu();
            System.out.print(">> ");
            String key = scanner.nextLine();

            Command command = this.commands.get(key);

            if(command == null){
                System.out.println("Invalid Option");
            }
            else
                command.execute();
        }
    }
}
