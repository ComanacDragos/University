package View;

import Controller.Controller;
import Exceptions.DivisionByZero;
import Exceptions.EmptyCollection;
import Exceptions.MyException;
import Model.ADTs.*;
import Model.Expressions.ArithmeticExpression;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;

import java.util.ArrayList;
import java.util.Scanner;

public class View {
    Controller controller;
    Scanner console;
    ArrayList<IStatement> programs;
    String programsMenu;

    public View(Controller controller){
        this.controller = controller;
        this.console = new Scanner(System.in);
        this.setupPrograms();
    }

    void printMenu(){
        String builder = "1. Input a program\n" +
                "2. Complete execution\n" +
                //"3. Print mode\n" +
                //"4. Normal mode\n" +
                "x. Exit\n";
        System.out.println(builder);
    }

    public void start(){
        while(true){
            this.printMenu();
            System.out.print(">> ");
            char choice = console.next().charAt(0);

            switch (choice) {
                case '1' -> this.inputProgram();
                case '2' -> this.completeExecution();
                case '3' -> this.printMode();
                case '4' -> this.normalMode();
                case 'x' -> {
                    return;
                }
                default -> System.out.println("Bad command");
            }
        }
    }

    void inputProgram(){
        System.out.print(programsMenu);
        System.out.print(">> ");
        int choice = this.console.nextInt() - 1;
        while(choice < 0 || choice >= programs.size()){
            System.out.println("Bad choice");
            System.out.print(">> ");
            choice = this.console.nextInt() - 1;
        }

        MyIStack<IStatement> executionStack = new MyStack<>();
        executionStack.push(programs.get(choice));
        MyIDictionary<String, IValue> symbolsTable = new MyDictionary<>();
        MyIList<IValue> out = new MyList<>();

        ProgramState newProgram = new ProgramState(executionStack, symbolsTable, out, programs.get(choice));
        this.controller.addProgramState(newProgram);
    }

    void completeExecution(){
        try{
            this.controller.executeAllSteps();
        } catch (MyException | EmptyCollection | DivisionByZero exception) {
            System.out.println(exception.getMessage() + '\n');
        }
    }

    void printMode(){
        this.controller.setPrintFlag(true);
    }

    void normalMode(){
        this.controller.setPrintFlag(false);
    }

    void setupPrograms(){
        this.programs = new ArrayList<>();
        this.programsMenu = "";

        this.programsMenu += "1. int v; v=2; Print(v)\n";
        IStatement ex1 = new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))
                )
        );
        this.programs.add(ex1);

        this.programsMenu += "2. int a; int b; a=2+3*5; b=a+1; Print(b)\n";

        IStatement ex2 = new CompoundStatement(
                new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement("b", new IntType()),
                                new AssignStatement("a", new ArithmeticExpression(
                                        new ValueExpression(new IntValue(2)),
                                        new ArithmeticExpression(
                                                new ValueExpression(new IntValue(3)),
                                                new ValueExpression(new IntValue(5)),
                                                '*'
                                        ),
                                        '+'
                                ))
                                ),
                        new CompoundStatement(
                                new AssignStatement("b", new ArithmeticExpression(
                                        new VariableExpression("a"),
                                        new ValueExpression(new IntValue(1)),
                                        '+'
                                )),
                                new PrintStatement(new VariableExpression("b"))
                        )
                )
        );
        this.programs.add(ex2);

        this.programsMenu += "3. bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)\n";

        IStatement ex3 = new CompoundStatement(
                new VariableDeclarationStatement("a", new BoolType()),
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement("v", new IntType()),
                                new AssignStatement("a", new ValueExpression(new BoolValue(true)))
                                ),
                        new CompoundStatement(
                                new IfStatement(
                                        new VariableExpression("a"),
                                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                        new AssignStatement("v", new ValueExpression(new IntValue(3)))
                                ),
                                new PrintStatement(new VariableExpression("v"))
                                ))
        );
        this.programs.add(ex3);

        this.programsMenu += "4. int a; a=10/0; Print(a)\n";

        IStatement ex4 = new CompoundStatement(
                new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(
                        new AssignStatement("a", new ArithmeticExpression(
                                new ValueExpression(new IntValue(10)),
                                new ValueExpression(new IntValue(0)),
                                '/'
                        )),
                        new PrintStatement(new VariableExpression("a"))
                )
        );
        this.programs.add(ex4);

        this.programsMenu += "5. int a; a=10/2; Print(b)\n";

        IStatement ex5 = new CompoundStatement(
                new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(
                        new AssignStatement("a", new ArithmeticExpression(
                                new ValueExpression(new IntValue(10)),
                                new ValueExpression(new IntValue(2)),
                                '/'
                        )),
                        new PrintStatement(new VariableExpression("b"))
                )
        );
        this.programs.add(ex5);
    }
}
