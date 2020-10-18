package Model;
import Model.adt.IDict;
import Model.adt.IList;
import Model.adt.IStack;
import Model.stmt.IStmt;

public class PrgState {

    IStack<IStmt> exeStack;
    IDict<String, Integer> symTable;
    IList<Integer> out;
    IStmt originalProgram; //optional field, but good to have

}