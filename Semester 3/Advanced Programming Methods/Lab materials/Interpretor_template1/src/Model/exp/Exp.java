package Model.exp;
import Model.adt.IDict;

public abstract class Exp {

    public abstract int eval(IDict<String,Integer> symTable);
    public abstract String toString();
}
