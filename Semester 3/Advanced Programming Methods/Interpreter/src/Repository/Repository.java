package Repository;

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
        return this.programs.get(0).deepCopy();
    }

    @Override
    public void addProgram(ProgramState newProgram) {
        this.programs.add(newProgram);
    }

    @Override
    public void logProgramStateExec(ProgramState programState) throws MyException {
        try (PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)))) {
            logFile.println(programState.toString());
        } catch (IOException e) {
            throw new MyException("ERROR: " + e.getMessage());
        }
    }

    @Override
    public void emptyLogFile() throws MyException {
        try (PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath)))) {
            writer.print("");
        } catch (IOException e) {
            throw new MyException("ERROR: " + e.getMessage());
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
