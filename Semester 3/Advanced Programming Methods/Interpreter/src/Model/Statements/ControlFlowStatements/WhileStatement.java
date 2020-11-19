package Model.Statements.ControlFlowStatements;

import Exceptions.MyException;
import Model.ADTs.MyIStack;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;


public class WhileStatement implements IStatement {
    IExpression expression;
    IStatement statement;

    int maxNumberOfIterations;

    public WhileStatement(IExpression expression, IStatement statement) {
        this.expression = expression;
        this.statement = statement;
        this.maxNumberOfIterations = 1000;
    }

    public IExpression getExpression() {
        return expression;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    public IStatement getStatement() {
        return statement;
    }

    public void setStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIStack<IStatement> executionStack = state.getExecutionStack();
        IValue value = this.expression.eval(state.getSymbolsTable(), state.getHeap());

        if(value.getType().equals(new BoolType())){
            BoolValue boolValue = (BoolValue) value;
            this.maxNumberOfIterations -= 1;

            if(this.maxNumberOfIterations == 0){
                throw new MyException("Maximum number of iterations: 1000 has been reached");
            }
            if(boolValue.getValue()){
                   executionStack.push(this);
                   executionStack.push(this.statement);
            }
        }
        else{
            throw new MyException("Expression must be a boolean");
        }

        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(this.expression.deepCopy(), this.statement.deepCopy());
    }

    @Override
    public String toString() {
        return "while(" + this.expression.toString() + "){\n" + this.statement.toString() + "\n}";
    }
}
