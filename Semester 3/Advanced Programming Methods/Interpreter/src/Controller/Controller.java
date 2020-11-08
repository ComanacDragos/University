package Controller;

import Exceptions.EmptyCollection;
import Exceptions.MyException;
import Model.ADTs.MyIStack;
import Model.ProgramState;
import Model.Statements.IStatement;
import Repository.IRepository;

public class Controller {
    IRepository repository;

    public Controller(IRepository repository){
        this.repository = repository;
    }

    public IRepository getRepository() {
        return repository;
    }

    public void setRepository(IRepository repository) {
        this.repository = repository;
    }

    public void addProgramState(ProgramState newProgram){
        this.repository.addProgram(newProgram);
    }

    public ProgramState executeOneStep(ProgramState programState) throws MyException {
        MyIStack<IStatement> executionStack = programState.getExecutionStack();
        if(executionStack.isEmpty())
            throw new EmptyCollection("Empty execution stack");
        IStatement currentStatement = executionStack.pop();

        return currentStatement.execute(programState);
    }

    public void executeAllSteps() throws MyException {
        ProgramState programState = this.repository.getCurrentProgram();
        this.repository.emptyLogFile();

        this.repository.logProgramStateExec(programState);
        while(!programState.getExecutionStack().isEmpty()){
            this.executeOneStep(programState);
            this.repository.logProgramStateExec(programState);
        }
    }

    @Override
    public String toString() {
        return this.repository.toString();
    }
}
