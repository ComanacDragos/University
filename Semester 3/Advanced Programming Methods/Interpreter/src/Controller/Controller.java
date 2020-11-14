package Controller;

import Exceptions.EmptyCollection;
import Exceptions.MyException;
import Model.ADTs.MyIStack;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Values.IValue;
import Model.Values.ReferenceValue;
import Repository.IRepository;

import java.util.Collection;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

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

    Map<Integer, IValue> garbageCollector(Set<Integer> validAddresses, Map<Integer, IValue> heap){
        return heap.entrySet().stream()
                .filter(e -> validAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    Set<Integer> getAddressesFromValues(Collection<IValue> values){
        return values.stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> ((ReferenceValue)v).getAddress())
                .collect(Collectors.toSet());
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

            Set<Integer> validAddresses = this.getAddressesFromValues(programState.getSymbolsTable().values());
            validAddresses.addAll(this.getAddressesFromValues(programState.getHeap().values()));

            programState.getHeap().setContent(
                    this.garbageCollector(
                            validAddresses,
                            programState.getHeap().getContent()
                    )
            );
            this.repository.logProgramStateExec(programState);
        }
    }

    @Override
    public String toString() {
        return this.repository.toString();
    }
}
