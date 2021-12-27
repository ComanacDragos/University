import java.io.Serializable;

public abstract class Message implements Serializable {
    public abstract void action(DistributedSharedMemory sharedMemory);

}
