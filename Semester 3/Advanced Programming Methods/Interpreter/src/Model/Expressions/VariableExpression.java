package Model.Expressions;

import Exceptions.MyException;
import Exceptions.VariableNotDefined;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Types.IType;
import Model.Values.IValue;

public class VariableExpression implements IExpression{
    String variableName;

    public VariableExpression(String variableName){
        this.variableName = variableName;
    }

    public String getVariableName() {
        return variableName;
    }

    public void setVariableName(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws VariableNotDefined {
        if(!symbolsTable.isDefined(variableName))
            throw new VariableNotDefined(this.variableName);
        return symbolsTable.lookup(variableName);
    }

    @Override
    public IType typeCheck(MyIDictionary<String, IType> typeEnvironment) throws MyException {
        try {
            return  typeEnvironment.lookup(this.variableName);
        }
        catch (MyException exception){
            throw new VariableNotDefined(this.variableName);
        }
    }

    @Override
    public VariableExpression deepCopy() {
        return new VariableExpression(this.variableName);
    }

    @Override
    public String toString() {
        return this.variableName;
    }
}
