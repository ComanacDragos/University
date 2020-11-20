package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIList;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Values.IValue;

public class PrintStatement implements IStatement{
    IExpression expression;

    public PrintStatement(IExpression expression){
        this.expression = expression;
    }

    public IExpression getExpression() {
        return expression;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIList<IValue> out = state.getOut();
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        out.add(this.expression.eval(symbolsTable, state.getHeap()));

        return null;
    }

    @Override
    public PrintStatement deepCopy() {
        return new PrintStatement(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "print(" + this.expression.toString() + ");";
    }
}
