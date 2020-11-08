package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Types.IType;
import Model.Values.IValue;

public class AssignStatement implements IStatement{
    String variable_name;
    IExpression expression;

    public AssignStatement(String variable_name, IExpression expression){
        this.variable_name = variable_name;
        this.expression = expression;
    }

    public IExpression getExpression() {
        return expression;
    }

    public String getVariable_name() {
        return variable_name;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    public void setVariable_name(String variable_name) {
        this.variable_name = variable_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        if(symbolsTable.isDefined(this.variable_name)){
            IValue value = this.expression.eval(symbolsTable);
            IType typeId = (symbolsTable.lookup(this.variable_name)).getType();

            if(value.getType().equals(typeId))
                symbolsTable.update(this.variable_name, value);
            else throw  new MyException("Declared type of variable " + variable_name + " and type of the assigned expression do not match");
        }
        else
            throw new MyException("The used variable " + variable_name + " was not declared before");

        return state;
    }

    @Override
    public AssignStatement deepCopy() {
        return new AssignStatement(this.variable_name, this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return this.variable_name + " = " + this.expression.toString() + ';';
    }
}
