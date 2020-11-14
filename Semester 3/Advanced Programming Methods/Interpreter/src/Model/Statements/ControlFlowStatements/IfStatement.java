package Model.Statements.ControlFlowStatements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIStack;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;


public class IfStatement implements IStatement {
    IExpression expression;
    IStatement thenStatement;
    IStatement elseStatement;

    public IfStatement(IExpression expression, IStatement thenStatement, IStatement elseStatement){
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    public IExpression getExpression() {
        return expression;
    }

    public IStatement getElseStatement() {
        return elseStatement;
    }

    public IStatement getThenStatement() {
        return thenStatement;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    public void setElseStatement(IStatement elseStatement) {
        this.elseStatement = elseStatement;
    }

    public void setThenStatement(IStatement thenStatement) {
        this.thenStatement = thenStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIStack<IStatement> executionStack = state.getExecutionStack();
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        IValue condition = this.expression.eval(symbolsTable, state.getHeap());

        if(condition.getType().equals(new BoolType())){
            BoolValue condition1 = (BoolValue) condition;
            if(condition1.getValue())
                executionStack.push(this.thenStatement);
            else
                executionStack.push(this.elseStatement);
        }
        else
            throw new MyException("Conditional expression is not a boolean");

        return state;
    }

    @Override
    public IfStatement deepCopy() {
        return new IfStatement(this.expression.deepCopy(), this.thenStatement.deepCopy(), this.elseStatement.deepCopy());
    }

    @Override
    public String toString() {
        return "IF (" + this.expression.toString() + ") THEN (" + this.thenStatement.toString() + ") ELSE (" + this.elseStatement.toString() + "));";
    }
}
