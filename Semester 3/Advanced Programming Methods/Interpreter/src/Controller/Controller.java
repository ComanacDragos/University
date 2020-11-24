package Controller;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ProgramState;
import Model.Values.IValue;
import Model.Values.ReferenceValue;
import Repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    IRepository repository;
    ExecutorService executorService;

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

    List<ProgramState> removeCompletedPrograms(List<ProgramState> inProgramsList){
        return inProgramsList.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    Map<Integer, IValue> garbageCollector(List<Integer> validAddresses, Map<Integer, IValue> heap){
        return heap.entrySet().stream()
                .filter(e -> validAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    List<Integer> getAddressesFromValues(Collection<IValue> values){
        return values.stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> ((ReferenceValue)v).getAddress())
                .collect(Collectors.toList());
    }

    List<Integer> getValidAddresses(){
        List<Integer> validAddresses = this.getAddressesFromValues(
                this.repository
                        .getPrograms()
                        .get(0)
                        .getHeap()
                        .values()
        );

        this.repository.getPrograms().stream()
            .map(ProgramState::getSymbolsTable)
            .map(MyIDictionary::values)
            .map(this::getAddressesFromValues)
            .forEach(validAddresses::addAll);

         return validAddresses;
    }

    void oneStepForAllPrograms(List<ProgramState> programStates){
        programStates.forEach(program -> this.repository.logProgramStateExec(program));

        List<Callable<ProgramState>> callables = programStates.stream()
                .map(p -> (Callable<ProgramState>)(p::executeOneStep))
                .collect(Collectors.toList());

        List<ProgramState> newProgramsList = new LinkedList<>();
        try {
            newProgramsList = this.executorService.invokeAll(callables).stream()
                    .map(future ->{
                        ProgramState toReturn = null;
                        try{
                            toReturn = future.get();
                        }
                        catch (MyException | InterruptedException | ExecutionException exception){
                            System.out.println(exception.getMessage());
                            System.exit(1);
                        }
                        return toReturn;
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());
        }
        catch (InterruptedException exception){
            System.out.println(exception.getMessage());
            System.exit(1);
        }

        programStates.addAll(newProgramsList);

        programStates.forEach(program -> this.repository.logProgramStateExec(program));

        this.repository.setPrograms(programStates);
    }

    public void executeAllSteps() throws MyException {
        this.repository.emptyLogFile();

        this.executorService = Executors.newFixedThreadPool(2);
        List<ProgramState> programStates = this.removeCompletedPrograms(this.repository.getPrograms());

        while(programStates.size() > 0){
            MyIDictionary<Integer, IValue> heap = this.repository.getPrograms().get(0).getHeap();

            heap.setContent(
                    this.garbageCollector(
                            this.getValidAddresses(),
                            heap.getContent()
                    )
            );
            this.oneStepForAllPrograms(programStates);
            programStates = this.removeCompletedPrograms(this.repository.getPrograms());
        }
        this.executorService.shutdownNow();
        this.repository.setPrograms(programStates);
    }

    @Override
    public String toString() {
        return this.repository.toString();
    }
}
