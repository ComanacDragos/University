package Model.Statements.HeapStatements;

import Exceptions.MyException;
import Model.ProgramState;
import Model.Statements.IStatement;

public class WriteHeapStatement implements IStatement {
    String variableName;

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return null;
    }
}
