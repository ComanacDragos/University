import mpi.MPI;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DistributedSharedMemory {
    int process = MPI.COMM_WORLD.Rank();

    private final Map<Variable, Integer> memory = new HashMap<>();
    private final Map<Variable, Set<Integer>> observingProcesses = new HashMap<>();
    private final Set<Integer> allProcesses = new HashSet<>();

    Lock lock = new ReentrantLock();

    public DistributedSharedMemory(){
        for(Variable var : Variable.values()){
            memory.put(var, 0);
        }
        memory.keySet().forEach(var -> observingProcesses.put(var, new HashSet<>()));
        for(int i=0;i<MPI.COMM_WORLD.Size();i++)
            allProcesses.add(i);
    }

    public void observe(Variable variable, Integer process){
        observingProcesses.get(variable).add(process);
    }

    public void updateVariable(Variable variable, Integer value){
        lock.lock();
        //setVariable(variable, value);
        sendTo(new UpdateMessage(variable, value), observingProcesses.get(variable));

        lock.unlock();
    }

    public void compareAndExchange(Variable variable, int oldValue, int newValue){
        lock.lock();
        if(memory.get(variable).equals(oldValue)) {
            //setVariable(variable, newValue);
            sendTo(new CompareAndExchangeMessage(variable, oldValue, newValue), observingProcesses.get(variable));
        }
        lock.unlock();
    }

    public void setVariable(Variable variable, int value){
        lock.lock();
        if(observingProcesses.get(variable).contains(process)){
            memory.put(variable, value);
        }else{
            Logger.log("Process is not observing " + variable + ", can't set it to " + value);
        }
        lock.unlock();
    }

    public void sendTo(Message message, Set<Integer> processes){
        Message[] messages = new Message[]{message};
        //Logger.log("Sending to " + processes + " -> " + message);
        lock.unlock();
        for(Integer  i : processes){
            MPI.COMM_WORLD.Send(messages, 0, 1, MPI.OBJECT, i, 0);
            Logger.log("Sent to " + i + " : " + message);
        }
        lock.lock();
    }

    public void close(){
        lock.lock();
        sendTo(new CloseMessage(), allProcesses);
        lock.unlock();
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder("Shared Memory\n");
        memory.entrySet().forEach(e -> builder
                .append(e.getKey())
                .append(" = ")
                .append(e.getValue())
                .append("\n")
        );
        builder.append("Observers\n");
        observingProcesses.entrySet().forEach(e -> builder
                .append(e.getKey())
                .append(" -> ")
                .append(e.getValue())
                .append("\n")
        );
        return builder.toString();
    }

    public Set<Integer> getAllProcesses() {
        return allProcesses;
    }
}
