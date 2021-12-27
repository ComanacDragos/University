import mpi.MPI;
import mpi.Status;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

public class Observer extends Thread{
    DistributedSharedMemory sharedMemory;
    Set<Integer> closedProcesses = new HashSet<>();
    List<Message> messages = new LinkedList<>();

    public Observer(DistributedSharedMemory sharedMemory) {
        this.sharedMemory = sharedMemory;

    }

    public void run(){
        Message[] messageBuffer = new Message[1];
        Logger.log("waiting for messages...");
        boolean running = true;
        while (running){
            Status status = MPI.COMM_WORLD.Recv(messageBuffer, 0, 1, MPI.OBJECT, MPI.ANY_SOURCE, 0);
            if(messageBuffer[0] instanceof CloseMessage) {
                closedProcesses.add(((CloseMessage) messageBuffer[0]).process);
                if(closedProcesses.equals(sharedMemory.getAllProcesses()))
                    running = false;
            }
            else {
                messageBuffer[0].action(sharedMemory);
            }
            Logger.log("Received: " + messageBuffer[0] + " from " + status.source);
        }
    }
}
