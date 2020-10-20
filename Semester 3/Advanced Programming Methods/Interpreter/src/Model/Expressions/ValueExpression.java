package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Values.IValue;

public class ValueExpression implements IExpression{
    IValue value;

    public ValueExpression(IValue value){
        this.value = value;
    }

    public IValue getValue() {
        return value;
    }

    public void setValue(IValue value) {
        this.value = value;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable) throws MyException {
        return this.value;
    }

    @Override
    public String toString() {
        return this.value.toString();
    }
}
