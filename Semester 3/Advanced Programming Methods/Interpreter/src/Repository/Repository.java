package Repository;

import Exceptions.DivisionByZero;
import Exceptions.EmptyCollection;
import Exceptions.MyException;
import Model.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Repository implements IRepository{
    ArrayList<ProgramState> programs;
    String logFilePath;

    public Repository(String logFilePath){
        this.programs = new ArrayList<>();
        this.logFilePath = logFilePath;
    }

    @Override
    public ProgramState getCurrentProgram() throws EmptyCollection {
        if(this.programs.isEmpty())
            throw new EmptyCollection("Empty repository");
        return this.programs.get(0);
    }

    @Override
    public void addProgram(ProgramState newProgram) {
        this.programs.add(newProgram);
    }

    @Override
    public void logProgramStateExec() throws MyException {
        PrintWriter logFile = null;
        try {
            logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
            logFile.println(this.getCurrentProgram().toString());
        }
        catch (IOException e) {
            throw new MyException("ERROR: " + e.getMessage());
        }
        finally {
            if(logFile != null)
                logFile.close();
        }
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for(ProgramState program: this.programs)
            builder.append(program.toString()).append('\n');
        return builder.toString();
    }
}
