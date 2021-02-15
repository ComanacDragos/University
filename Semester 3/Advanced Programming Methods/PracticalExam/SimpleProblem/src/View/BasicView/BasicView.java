package View.BasicView;

/*
public class BasicView {
    Controller controller;
    Scanner console;
    ArrayList<IStatement> programs;
    String programsMenu;

    public BasicView(Controller controller){
        this.controller = controller;
        this.console = new Scanner(System.in);
        this.setupPrograms();
    }

    void printMenu(){
        String builder = "1. Input a program\n" +
                "2. Complete execution\n" +
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
                case '2' -> {
                    this.completeExecution();
                    return;
                }
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
        MyIDictionary<String, BufferedReader> fileTable = new MyDictionary<>();

        ProgramState newProgram = new ProgramState(executionStack, symbolsTable, out, fileTable, programs.get(choice));
        this.controller.addProgramState(newProgram);
    }

    void completeExecution(){
        try{
            this.controller.executeAllSteps();
        } catch (MyException exception) {
            System.out.println(exception.getMessage() + '\n');
        }
    }

    IStatement assembleStatement(IStatement... statements){
        if(statements.length == 0)
            return new NopStatement();
        if(statements.length == 1)
            return statements[0];
        if(statements.length == 2)
            return new CompoundStatement(statements[0], statements[1]);
        return new CompoundStatement(statements[0], assembleStatement(Arrays.copyOfRange(statements, 1, statements.length)));
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
                                                ArithmeticExpression.ArithmeticOperation.MULTIPLICATION
                                        ),
                                        ArithmeticExpression.ArithmeticOperation.ADDITION
                                ))
                                ),
                        new CompoundStatement(
                                new AssignStatement("b", new ArithmeticExpression(
                                        new VariableExpression("a"),
                                        new ValueExpression(new IntValue(1)),
                                        ArithmeticExpression.ArithmeticOperation.ADDITION
                                )),
                                new PrintStatement(new VariableExpression("b"))
                        )
                )
        );
        this.programs.add(ex2);

        this.programsMenu += "3. bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)\n";

        IStatement ex3 = this.assembleStatement(
                new VariableDeclarationStatement("a", new BoolType()),
                new VariableDeclarationStatement("v", new IntType()),
                new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                new IfStatement(
                        new VariableExpression("a"),
                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new AssignStatement("v", new ValueExpression(new IntValue(3)))
                ),
                new PrintStatement(new VariableExpression("v"))
        );

        this.programs.add(ex3);

        this.programsMenu += "4. int a; a=10/0; Print(a)\n";

        IStatement ex4 = new CompoundStatement(
                new VariableDeclarationStatement("a", new IntType()),
                new CompoundStatement(
                        new AssignStatement("a", new ArithmeticExpression(
                                new ValueExpression(new IntValue(10)),
                                new ValueExpression(new IntValue(0)),
                                ArithmeticExpression.ArithmeticOperation.DIVISION
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
                                ArithmeticExpression.ArithmeticOperation.DIVISION
                        )),
                        new PrintStatement(new VariableExpression("b"))
                )
        );
        this.programs.add(ex5);

        this.programsMenu += "6. bool a; a = true; bool b; Print(a && b); Print(a || b)\n";

        IStatement ex6 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new BoolType()),
                                new AssignStatement("a", new ValueExpression(new BoolValue(true)))
                        ),
                        new VariableDeclarationStatement("b", new BoolType())
                ),
                new CompoundStatement(
                        new PrintStatement(
                                new LogicExpression(
                                        new VariableExpression("a"),
                                        new VariableExpression("b"),
                                        LogicExpression.LogicOperand.AND
                                )
                        ),
                        new PrintStatement(
                                new LogicExpression(
                                        new VariableExpression("a"),
                                        new VariableExpression("b"),
                                        LogicExpression.LogicOperand.OR
                                )
                        )
                )
        );
        this.programs.add(ex6);

        this.programsMenu += "7. read file\n";

        IStatement ex7 = new CompoundStatement(
                new CompoundStatement(
                       new VariableDeclarationStatement("varf", new StringType()),
                       new CompoundStatement(
                               new AssignStatement("varf", new ValueExpression(new StringValue("src/Files/test.in"))),
                                new CompoundStatement(
                                        new OpenReadFileStatement(new ValueExpression(new StringValue("src/Files/test.in"))),
                                        new VariableDeclarationStatement("varc", new IntType())
                                )
                       )
                ),
                new CompoundStatement(
                        new CompoundStatement(
                                new ReadFileStatement(new ValueExpression(new StringValue("src/Files/test.in")), "varc"),
                                new PrintStatement(new VariableExpression("varc"))
                        ),
                        new CompoundStatement(
                                new CompoundStatement(
                                       new ReadFileStatement(new ValueExpression(new StringValue("src/Files/test.in")), "varc"),
                                        new PrintStatement(new VariableExpression("varc"))
                                ),
                                new CloseReadFile(new ValueExpression(new StringValue("src/Files/test.in")))
                        )
                )
        );
        this.programs.add(ex7);
    }
}
*/