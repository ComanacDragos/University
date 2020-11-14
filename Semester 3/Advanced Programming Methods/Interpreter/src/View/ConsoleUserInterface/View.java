package View.ConsoleUserInterface;

import Controller.Controller;
import Model.ADTs.*;
import Model.Expressions.*;
import Model.Expressions.BinaryExpressions.ArithmeticExpression;
import Model.Expressions.BinaryExpressions.LogicExpression;
import Model.Expressions.BinaryExpressions.RelationalExpression;
import Model.Expressions.UnaryExpressions.ReadHeapExpression;
import Model.ProgramState;
import Model.Statements.*;
import Model.Statements.ControlFlowStatements.IfStatement;
import Model.Statements.ControlFlowStatements.WhileStatement;
import Model.Statements.FileStatements.CloseReadFile;
import Model.Statements.FileStatements.OpenReadFileStatement;
import Model.Statements.FileStatements.ReadFileStatement;
import Model.Statements.HeapStatements.NewStatement;
import Model.Statements.HeapStatements.WriteHeapStatement;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.ReferenceType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.IRepository;
import Repository.Repository;

import java.io.BufferedReader;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class View {
    TextMenu menu;
    Map<IStatement, String> programsDescriptions;

    public View(){
        this.menu = new TextMenu();
        this.programsDescriptions = new LinkedHashMap<>();
        this.setupPrograms();
    }

    public void start(){
        this.menu.show();
    }

    void setupPrograms(){
        IStatement ex1 = new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))
                )
        );
        this.programsDescriptions.put(ex1, "int v; v=2; Print(v)");

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
        this.programsDescriptions.put(ex2, "int a; int b; a=2+3*5; b=a+1; Print(b)");


        IStatement ex3 = new CompoundStatement(
            new CompoundStatement(
                    new CompoundStatement(
                            new VariableDeclarationStatement("a", new BoolType()),
                            new VariableDeclarationStatement("v", new IntType())
                    ),
                    new AssignStatement("a", new ValueExpression(new BoolValue(true)))
                    ),
            new CompoundStatement(
                    new IfStatement(
                            new VariableExpression("a"),
                            new AssignStatement("v", new ValueExpression(new IntValue(2))),
                            new AssignStatement("v", new ValueExpression(new IntValue(3)))
                    ),
                    new PrintStatement(new VariableExpression("v"))
            )
        );

        this.programsDescriptions.put(ex3, "bool a; int v; a=true; (If a Then v=2 Else v=3); Print(v)");

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
        this.programsDescriptions.put(ex4, "int a; a=10/0; Print(a)");

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
        this.programsDescriptions.put(ex5, "int a; a=10/2; Print(b)");

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
        this.programsDescriptions.put(ex6, "bool a; a = true; bool b; Print(a && b); Print(a || b)");

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
        this.programsDescriptions.put(ex7, "string varf;varf=\"test.in\";openRFile(varf);int varc; readFile(varf,varc);print(varc); readFile(varf,varc);print(varc);closeRFile(varf)");

        IStatement ex8 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement("a", new IntType()),
                                new VariableDeclarationStatement("b", new IntType())
                        ),
                        new CompoundStatement(
                                new AssignStatement("a", new ValueExpression(new IntValue(5))),
                                new AssignStatement("b", new ValueExpression(new IntValue(10)))
                        )
                ),
                new CompoundStatement(
                        new CompoundStatement(
                                new PrintStatement(
                                        new RelationalExpression(
                                                new VariableExpression("a"),
                                                new VariableExpression("b"),
                                                RelationalExpression.RelationalOperation.NOT_EQUAL
                                        )
                                ),
                                        new PrintStatement(
                                                new RelationalExpression(
                                                        new VariableExpression("a"),
                                                        new VariableExpression("b"),
                                                        RelationalExpression.RelationalOperation.LESS_THAN
                                                )
                                        )
                        ),
                        new CompoundStatement(
                                new PrintStatement(
                                        new RelationalExpression(
                                                new VariableExpression("a"),
                                                new VariableExpression("b"),
                                                RelationalExpression.RelationalOperation.EQUAL
                                        )
                                ),
                                new PrintStatement(
                                        new RelationalExpression(
                                                new VariableExpression("a"),
                                                new VariableExpression("b"),
                                                RelationalExpression.RelationalOperation.GREATER_THAN_OR_EQUAL
                                        )
                                )
                        )
                )
        );

        this.programsDescriptions.put(ex8, "int a;int b;a=5;b=10; print(a!=b);print(a<b);print(a==b);print(a>=b)");


        IStatement ex9 = new CompoundStatement(
                new CompoundStatement(
                      new CompoundStatement(
                              new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                              new NewStatement("v", new ValueExpression(new IntValue(20)))
                      ),
                      new CompoundStatement(
                            new VariableDeclarationStatement(
                                    "a",
                                    new ReferenceType(
                                            new ReferenceType(
                                                    new IntType()
                                            )
                                    )
                            ),
                              new NewStatement("a", new VariableExpression("v"))
                      )
                ),
                new CompoundStatement(
                        new PrintStatement(new VariableExpression("v")),
                        new PrintStatement(new VariableExpression("a"))
                )
        );

        this.programsDescriptions.put(ex9, "ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)");

        IStatement ex10 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                                new NewStatement("v", new ValueExpression(new IntValue(20)))
                        ),
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "a",
                                        new ReferenceType(
                                                new ReferenceType(
                                                        new StringType()
                                                )
                                        )
                                ),
                                new NewStatement("a", new VariableExpression("v"))
                        )
                ),
                new CompoundStatement(
                        new PrintStatement(new VariableExpression("v")),
                        new PrintStatement(new VariableExpression("a"))
                )
        );

        this.programsDescriptions.put(ex10, "ref int v;new(v,20);Ref Ref string a; new(a,v);print(v);print(a)");

        IStatement ex11 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement("v",
                                        new ReferenceType(
                                                new IntType()
                                        )
                                ),
                                new NewStatement("v",
                                        new ValueExpression(
                                            new IntValue(20)
                                        )
                                )
                        ),
                        new CompoundStatement(
                                new VariableDeclarationStatement("a",
                                        new ReferenceType(
                                                new ReferenceType(
                                                        new IntType()
                                                )
                                        )
                                ),
                                new NewStatement("a",
                                        new VariableExpression("v")
                                )
                        )
                ),
                new CompoundStatement(
                        new PrintStatement(
                                new ReadHeapExpression(
                                        new VariableExpression("v")
                                )
                        ),
                        new PrintStatement(
                                new ArithmeticExpression(
                                        new ReadHeapExpression(
                                                new ReadHeapExpression(
                                                        new VariableExpression("a")
                                                )
                                        ),
                                        new ValueExpression(new IntValue(5)),
                                        ArithmeticExpression.ArithmeticOperation.ADDITION
                                )
                        )
                )
        );

        this.programsDescriptions.put(ex11, "ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)");

        IStatement ex12 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "v",
                                        new ReferenceType(
                                                new IntType()
                                        )
                                ),
                                new NewStatement(
                                        "v",
                                        new ValueExpression(
                                                new IntValue(20)
                                        )
                                )
                        ),
                        new CompoundStatement(
                                new PrintStatement(
                                        new ReadHeapExpression(
                                                new VariableExpression("v")
                                        )
                                ),
                                new WriteHeapStatement(
                                        "v",
                                        new ValueExpression(
                                                new IntValue(30)
                                        )
                                )
                        )
                ),
                new PrintStatement(
                        new ArithmeticExpression(
                                new ReadHeapExpression(
                                        new VariableExpression("v")
                                ),
                                new ValueExpression(
                                        new IntValue(5)
                                ),
                                ArithmeticExpression.ArithmeticOperation.ADDITION
                        )
                )
        );

        this.programsDescriptions.put(ex12, "ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);");

        IStatement ex13 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "v",
                                        new ReferenceType(
                                                new IntType()
                                        )
                                ),
                                new NewStatement(
                                        "v",
                                        new ValueExpression(
                                                new IntValue(20)
                                        )
                                )
                        ),
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "a",
                                        new ReferenceType(
                                                new ReferenceType(
                                                        new IntType()
                                                )
                                        )
                                ),
                                new NewStatement(
                                        "a",
                                        new VariableExpression("v")
                                )
                        )
                ),
                new CompoundStatement(
                        new NewStatement(
                                "v",
                                new ValueExpression(
                                        new IntValue(30)
                                )
                        ),
                        new PrintStatement(
                                new ReadHeapExpression(
                                        new ReadHeapExpression(
                                                new VariableExpression("a")
                                        )
                                )
                        )
                )
        );

        this.programsDescriptions.put(ex13, "ref int v;new(v,20);ref ref int a; new(a,v); new(v,30);print(rH(rH(a)));");

        IStatement ex14 = new CompoundStatement(
                new CompoundStatement(
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "v",
                                        new ReferenceType(
                                                new IntType()
                                        )
                                ),
                                new NewStatement(
                                        "v",
                                        new ValueExpression(
                                                new IntValue(20)
                                        )
                                )
                        ),
                        new CompoundStatement(
                                new VariableDeclarationStatement(
                                        "a",
                                        new ReferenceType(
                                                new ReferenceType(
                                                        new IntType()
                                                )
                                        )
                                ),
                                new NewStatement(
                                        "a",
                                        new VariableExpression("v")
                                )
                        )
                ),
                new CompoundStatement(
                        new NewStatement(
                                "v",
                                new ValueExpression(
                                        new IntValue(30)
                                )
                        ),
                        new CompoundStatement(
                                new PrintStatement(
                                        new ReadHeapExpression(
                                                new ReadHeapExpression(
                                                        new VariableExpression("a")
                                                )
                                        )
                                ),
                                new CompoundStatement(
                                        new NewStatement(
                                                "a",
                                                new VariableExpression("v")
                                        ),
                                        new PrintStatement(
                                                new VariableExpression("a")
                                        )
                                )
                        )
                )
        );

        this.programsDescriptions.put(ex14, "ref int v;new(v,20);ref ref int a; new(a,v); new(v,30);print(rH(rH(a)));new(a,v);print(a)");

        IStatement ex15 = new CompoundStatement(
                new CompoundStatement(
                        new VariableDeclarationStatement(
                                "v",
                                new IntType()),
                        new AssignStatement(
                                "v",
                                new ValueExpression(
                                        new IntValue(4)
                                )
                        )
                ),
                new CompoundStatement(
                        new WhileStatement(
                                new RelationalExpression(
                                        new VariableExpression("v"),
                                        new ValueExpression(
                                                new IntValue(0)
                                        ),
                                        RelationalExpression.RelationalOperation.GREATER_THAN
                                ),
                                new CompoundStatement(
                                        new PrintStatement(
                                                new VariableExpression("v")
                                        ),
                                        new AssignStatement(
                                                "v",
                                                new ArithmeticExpression(
                                                        new VariableExpression("v"),
                                                        new ValueExpression(
                                                                new IntValue(1)
                                                        ),
                                                        ArithmeticExpression.ArithmeticOperation.SUBTRACTION
                                                )
                                        )
                                )
                        ),
                        new PrintStatement(
                                new VariableExpression("v")
                        )
                )
        );

        this.programsDescriptions.put(ex15, "int v; v=4; (while (v>0) print(v);v=v-1);print(v)");

        AtomicInteger currentKey = new AtomicInteger(1);
        this.programsDescriptions.forEach(
                (statement, description) ->{
                    MyIStack<IStatement> executionStack = new MyStack<>();
                    executionStack.push(statement);
                    MyIDictionary<String, IValue> symbolsTable = new MyDictionary<>();
                    MyIList<IValue> out = new MyList<>();
                    MyIDictionary<String, BufferedReader> fileTable = new MyDictionary<>();
                    MyHeap heap = new MyHeap();

                    ProgramState newProgram = new ProgramState(executionStack, symbolsTable, out, fileTable, heap, statement);

                    IRepository repository = new Repository("src/Files/log" + currentKey + ".txt");
                    Controller controller = new Controller(repository);
                    controller.addProgramState(newProgram);

                    this.menu.addCommand(new RunExample(String.valueOf(currentKey.get()), description, controller));
                    currentKey.getAndIncrement();
                }
        );

        this.menu.addCommand(new ExitCommand("x", "exit"));
        }
    }

