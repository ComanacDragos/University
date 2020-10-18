package Model.exp;
import Model.adt.IDict;

public class VarExp extends Exp{
    String id;

    public int eval(IDict<String,Integer> symTable) {
        return symTable.lookup(id);
    }

    public String toString() {return id;}

}
