package Model.Statements;

import Exceptions.MyException;
import Model.ProgramState;

public class NopStatement implements IStatement{
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return state;
    }

    @Override
    public String toString() {
        return "NOP;";
    }

}
