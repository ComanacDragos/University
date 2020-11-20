package Repository;

import Exceptions.MyException;
import Model.ProgramState;

import java.util.List;

public interface IRepository {
    List<ProgramState> getPrograms();

    void setPrograms(List<ProgramState> programs);

    void addProgram(ProgramState newProgram);

    void logProgramStateExec(ProgramState programState) throws MyException;

    void emptyLogFile() throws MyException;
}
