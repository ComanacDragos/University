package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Types.IType;
import Model.Values.IValue;

public class AssignStatement implements IStatement{
    String variableName;
    IExpression expression;

    public AssignStatement(String variableName, IExpression expression){
        this.variableName = variableName;
        this.expression = expression;
    }

    public IExpression getExpression() {
        return expression;
    }

    public String getVariableName() {
        return variableName;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    public void setVariableName(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        if(symbolsTable.isDefined(this.variableName)){
            IValue value = this.expression.eval(symbolsTable, state.getHeap());
            IType typeId = (symbolsTable.lookup(this.variableName)).getType();

            if(value.getType().equals(typeId))
                symbolsTable.update(this.variableName, value);
            else throw  new MyException("Declared type of variable " + variableName + " and type of the assigned expression do not match");
        }
        else
            throw new MyException("The used variable " + variableName + " was not declared before");

        return null;
    }

    @Override
    public AssignStatement deepCopy() {
        return new AssignStatement(this.variableName, this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return this.variableName + " = " + this.expression.toString() + ';';
    }
}
