package Model.exp;
import Model.adt.IDict;

public class ArithExp extends Exp{
    char op;
    Exp e1, e2;

    //constructor

    public int eval(IDict<String, Integer> symTable) {

        if (op == '+') return (e1.eval(symTable)+e2.eval(symTable));

        //...
        else
            if(e2.eval(symTable)==0) //throw new exception
    }

    public char getOp() {return this.op;}

    public Exp getFirst() {
        return this.e1;
    }

    public Exp getSecond() {
        return this.e2;
    }

    public String toString() { return e1.toString() + " " + op + " " + e2.toString(); }
}
