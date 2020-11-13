package Model.Expressions;

import Exceptions.VariableNotDefined;
import Model.ADTs.MyHeap;
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
    public IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws VariableNotDefined {
        if(!symbolsTable.isDefined(id))
            throw new VariableNotDefined("Variable " + id + " not defined");
        return symbolsTable.lookup(id);
    }

    @Override
    public VariableExpression deepCopy() {
        return new VariableExpression(this.id);
    }

    @Override
    public String toString() {
        return this.id;
    }
}
