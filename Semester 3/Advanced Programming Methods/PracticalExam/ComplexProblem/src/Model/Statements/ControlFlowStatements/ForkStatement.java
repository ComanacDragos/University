package Model.Statements.ControlFlowStatements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIStack;
import Model.ADTs.MyStack;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.IType;

public class ForkStatement implements IStatement {
    IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    public IStatement getStatement() {
        return statement;
    }

    public void setStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIStack<IStatement> newExecutionStack = new MyStack<>();
        newExecutionStack.push(statement);
        return new ProgramState(
                newExecutionStack,
                state.symbolsTableDeepCopy(),
                state.getOut(),
                state.getFileTable(),
                state.getHeap(),
                state.getLatchTable(),
                statement.deepCopy()
        );
    }

    @Override
    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnvironment) throws MyException {
        this.statement.typeCheck(typeEnvironment.shallowCopy());
        return typeEnvironment;
    }

    @Override
    public IStatement deepCopy() {
        return new ForkStatement(this.statement.deepCopy());
    }

    @Override
    public String toString() {
        return "fork(\n" + this.statement.toString() + "\n)";
    }
}
