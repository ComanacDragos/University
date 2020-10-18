package Model.exp;
import Model.adt.IDict;

public class ConstExp extends Exp{
    int number;

    public int eval(IDict<String,Integer> symTable) {
        return number;
    }

    public String toString() {
        return Integer.toString(number);
    }
}
