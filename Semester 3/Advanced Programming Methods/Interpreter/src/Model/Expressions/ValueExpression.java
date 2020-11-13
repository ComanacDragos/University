package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
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
    public IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException {
        return this.value;
    }

    @Override
    public ValueExpression deepCopy() {
        return new ValueExpression(this.value.deepCopy());
    }

    @Override
    public String toString() {
        return this.value.toString();
    }
}
