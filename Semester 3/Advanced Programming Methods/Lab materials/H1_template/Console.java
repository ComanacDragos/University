package View;


import Controller.Vegetable_Ctrl;
import CustomException.CustomException;
import Model.Ardei;
import Model.Rosii;
import Model.Vegetable;
import Model.Vinete;

import java.util.Scanner;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class Console {

    public Vegetable_Ctrl ctrl;

    public Console(Vegetable_Ctrl ctrl) {
        this.ctrl = ctrl;
    }

    public void printMenu(String[] options) {
        StringBuilder build = new StringBuilder();
        for (String str : options) {
            build.append(str);
        }
        System.out.print(build.toString());
    }


    public void addVeg(Vegetable v) {
        try{
            this.ctrl.add(v);
        }
        catch(CustomException e)
        {
            System.out.print(e);
        }
    }

    public Vegetable readVeg() {
        /*
        Reads a type of vegetable from the keyboard and returns it.
         */
        Scanner input = new Scanner(System.in);
        System.out.println("Vegetable weight: ");
        double weight;
        weight = input.nextDouble();
        System.out.println("Vegetable type: ");
        System.out.println("1. Rosie.");
        System.out.println("2. Ardei.");
        System.out.println("3. Vinata.");
        Vegetable v = null;
        switch (input.nextInt()) {
            case 1:
                v = new Rosii(weight);
                break;
            case 2:
                v = new Ardei(weight);
                break;
            case 3:
                v = new Vinete(weight);
                break;
            default:
                System.out.println("Nothing happened.\n");
        }
        return v;
    }

    public void removeVeg() {
        Scanner input = new Scanner(System.in);
        System.out.println("Id to remove: ");
        int index;
        index = input.nextInt();
        try
        {
            this.ctrl.remove(index);
        }
        catch(CustomException e)
        {
            System.out.print(e);
        }
    }

    public void filterVeg() {
        try {
            System.out.print(ctrl.filter());
        }
        catch (CustomException e)
        {
            System.out.print(e);
        }
    }
    public void menu()
    {
        String[] menuOptions = {"1.Add Vegetable.\n" +
                                "2.Remove Vegetable.\n"+
                                "3.Filter Vegetable (weight>0.2kg)\n"+
                                "0.Exit\n"};
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        printMenu(menuOptions);
        boolean done = false;
        while(!done)
        {
            int opt = -1;
            try{
                System.out.print("Select option: ");
                opt = Integer.parseInt(reader.readLine());
            }
            catch (Exception a) {
                System.out.print("Invalid option \n");
            }
            switch (opt){
                case 1:
                    Vegetable veg;
                    veg = readVeg();
                    addVeg(veg);
                    break;
                case 2:
                    removeVeg();
                    break;
                case 3:
                    filterVeg();
                    break;
                case 0:
                    done = true;
                    break;
                default:
                    break;
            }
            printMenu(menuOptions);
        }
    }

}
