import java.util.List;

public class Worker extends Thread{
    Task task;

    public Worker(MatrixRepo repo, List<MatrixEntry> elements) {
        this.task = new Task(repo, elements);
    }

    @Override
    public void run(){
        task.run();
    }
}
