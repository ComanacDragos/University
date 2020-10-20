package Repository;

import Exceptions.EmptyCollection;
import Model.ProgramState;

public interface IRepository {
    ProgramState getCurrentProgram() throws EmptyCollection;

    void addProgram(ProgramState newProgram);
}
