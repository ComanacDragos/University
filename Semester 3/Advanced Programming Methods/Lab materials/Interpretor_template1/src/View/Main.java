package View;
import Repo.Repo;
import Controller.Controller;
import Model.PrgState;
import Model.adt.IDict;
import Model.adt.Dict;
import Model.adt.IList;
import Model.adt.List;

public class Main {

    static Repo myRepository = new Repo();
    static Controller myController = new Controller(myRepository);

    public static void main(String[] args) {
        IStmt originalProgram = new IfStmt(new ConstExp(10),
                new CompStmt(new AssignStmt("v", new ConstExp(5)),
                        new PrintStmt(new ArithExp('/',
                                new VarExp("v"), new ConstExp(3)))),
                new PrintStmt(new ConstExp(100)));
        MyIStack<IStmt> exeStack = new MyStack<IStmt>();
        //exeStack.push(originalProgram);
        IDict<String, Integer> symTable = new Dict<String, Integer>();
        IList<Integer> out = new List<Integer>();
        PrgState myPrgState = new PrgState(exeStack, symTable, out, originalProgram);
        myController.addProgram(myPrgState);
        myController.allStep();
    }
}
