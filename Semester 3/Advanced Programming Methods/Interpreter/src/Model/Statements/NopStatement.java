package Model.Statements;

import Exceptions.MyException;
import Model.ProgramState;

public class NopStatement implements IStatement{
    String id;
    public NopStatement(String id) {
        this.id = id;
    }


    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }

    @Override
    public String toString() {
        return "NOP " + this.id + ';';
    }

}
