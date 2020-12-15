package Controller;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ProgramState;
import Model.Values.IValue;
import Model.Values.ReferenceValue;
import Repository.IRepository;
import Observer.MyObservable;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller extends MyObservable {
    IRepository repository;
    ExecutorService executorService;

    public Controller(IRepository repository){
        this.repository = repository;
    }

    public IRepository getRepository() {
        return repository;
    }

    public List<ProgramState> getPrograms(){
        return this.repository.getPrograms();
    }

    public void setRepositoryPrograms(List<ProgramState> programs){
        this.repository.setPrograms(programs);
        this.notyfiObservers();
    }

    public void setRepository(IRepository repository) {
        this.repository = repository;
    }

    public void setExecutorService(ExecutorService executorService) {
        this.executorService = executorService;
    }

    public ExecutorService getExecutorService() {
        return executorService;
    }

    public void addProgramState(ProgramState newProgram){
        this.repository.addProgram(newProgram);
    }

    public Optional<ProgramState> getProgram(Integer id){
        return this.repository.getPrograms().stream()
                .filter(p -> p.getProgramId().equals(id))
                .findFirst();
    }

    public List<ProgramState> removeCompletedPrograms(List<ProgramState> inProgramsList){
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

    public void oneStepForAllPrograms(List<ProgramState> programStates){
        programStates.forEach(program -> this.repository.logProgramStateExec(program));

        List<Callable<ProgramState>> callables = programStates.stream()
                .map(p -> (Callable<ProgramState>)(p::executeOneStep))
                .collect(Collectors.toList());

        List<ProgramState> newProgramsList = new LinkedList<>();
        try {
            List<String> exceptions = new LinkedList<>();
            newProgramsList = this.executorService.invokeAll(callables).stream()
                    .map(future ->{
                        ProgramState toReturn = null;
                        try{
                            toReturn = future.get();
                        }
                        catch (MyException | InterruptedException | ExecutionException exception){
                            //System.out.println(exception.getMessage());
                            //System.exit(1);
                            exceptions.add(exception.getMessage() + "\n");
                        }
                        return toReturn;
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());

            if(!exceptions.isEmpty()) {
                throw new MyException(
                        String.join("\n", exceptions)
                );
            }
        }
        catch (InterruptedException exception){
            System.out.println(exception.getMessage());
            System.exit(1);
        }

        programStates.addAll(newProgramsList);

        programStates.forEach(program -> this.repository.logProgramStateExec(program));

        this.repository.setPrograms(programStates);

        this.notyfiObservers();
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

    public void runGarbageCollector(){
        MyIDictionary<Integer, IValue> heap = this.repository.getPrograms().get(0).getHeap();

        heap.setContent(
                this.garbageCollector(
                        this.getValidAddresses(),
                        heap.getContent()
                )
        );

        this.notyfiObservers();
    }

    public void emptyLogFile(){
        this.repository.emptyLogFile();
    }

    @Override
    public String toString() {
        return this.repository.toString();
    }
}
