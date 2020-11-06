package Repository;

import Exceptions.EmptyCollection;
import Exceptions.MyException;
import Model.ProgramState;

public interface IRepository {
    ProgramState getCurrentProgram() throws EmptyCollection;

    void addProgram(ProgramState newProgram);

    void logProgramStateExec() throws MyException;
}
