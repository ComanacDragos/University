package Controller;

import Exceptions.DivisionByZero;
import Exceptions.EmptyCollection;
import Exceptions.MyException;
import Model.ADTs.MyIStack;
import Model.ADTs.MyList;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Values.IValue;
import Repository.IRepository;

public class Controller {
    IRepository repository;
    boolean printFlag;

    public Controller(IRepository repository){
        this.repository = repository;
        this.printFlag = false;
    }

    public IRepository getRepository() {
        return repository;
    }

    public void setRepository(IRepository repository) {
        this.repository = repository;
    }

    public void setPrintFlag(boolean printFlag) {
        this.printFlag = printFlag;
    }

    public void addProgramState(ProgramState newProgram){
        this.repository.addProgram(newProgram);
    }

    public ProgramState executeOneStep(ProgramState programState) throws EmptyCollection, MyException, DivisionByZero {
        MyIStack<IStatement> executionStack = programState.getExecutionStack();
        if(executionStack.isEmpty())
            throw new EmptyCollection("Empty execution stack");
        IStatement currentStatement = executionStack.pop();

        return currentStatement.execute(programState);
    }

    public void executeAllSteps() throws EmptyCollection, DivisionByZero, MyException {
        ProgramState programState = this.repository.getCurrentProgram();
        int step = 0;
        if(this.printFlag)
            System.out.println(String.valueOf(++step) + ". " + programState);

        while(!programState.getExecutionStack().isEmpty()){
            this.executeOneStep(programState);

            if(this.printFlag)
                System.out.println(++step + ". " + programState);
        }

        System.out.println(programState.getOut());
    }

    @Override
    public String toString() {
        return this.repository.toString();
    }
}
