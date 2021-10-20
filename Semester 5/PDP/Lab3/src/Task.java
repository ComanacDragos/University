import java.util.List;

public class Task implements Runnable{
    MatrixRepo repo;
    List<MatrixEntry> elements;

    public Task(MatrixRepo repo, List<MatrixEntry> elements) {
        this.repo = repo;
        this.elements = elements;
    }

    @Override
    public void run(){
        elements.forEach(repo::computeElement);
    }
}
