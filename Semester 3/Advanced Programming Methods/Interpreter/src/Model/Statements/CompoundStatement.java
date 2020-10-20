package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIStack;
import Model.ProgramState;

public class CompoundStatement implements IStatement{
    IStatement first;
    IStatement second;

    public CompoundStatement(IStatement first, IStatement second){
        this.first = first;
        this.second = second;
    }

    public IStatement getFirst() {
        return first;
    }

    public IStatement getSecond() {
        return second;
    }

    public void setFirst(IStatement first) {
        this.first = first;
    }

    public void setSecond(IStatement second) {
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIStack<IStatement> stack = state.getExecutionStack();
        stack.push(this.second);
        stack.push(this.first);

        return state;
    }

    @Override
    public String toString() {
        return '(' + this.first.toString() + ';' + this.second.toString() + ')';
    }
}
