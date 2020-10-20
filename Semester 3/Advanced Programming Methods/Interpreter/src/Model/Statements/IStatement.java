package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ProgramState;

public interface IStatement {
    ProgramState execute(ProgramState state) throws MyException, DivisionByZero;
}
