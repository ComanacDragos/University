package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Values.IValue;

public class VariableExpression implements IExpression{
    String id;

    public VariableExpression(String id){
        this.id = id;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable) throws MyException {
        return symbolsTable.lookup(id);
    }

    @Override
    public String toString() {
        return this.id;
    }
}
