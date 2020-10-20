package Repository;

import Exceptions.EmptyCollection;
import Model.ProgramState;

import java.util.ArrayList;

public class Repository implements IRepository{
    ArrayList<ProgramState> programs;

    public Repository(){
        this.programs = new ArrayList<>();
    }

    @Override
    public ProgramState getCurrentProgram() throws EmptyCollection {
        if(this.programs.isEmpty())
            throw new EmptyCollection("Empty repository");
        return this.programs.get(this.programs.size() - 1);
    }

    @Override
    public void addProgram(ProgramState newProgram) {
        this.programs.add(newProgram);
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for(ProgramState program: this.programs)
            builder.append(program.toString()).append('\n');
        return builder.toString();
    }
}
