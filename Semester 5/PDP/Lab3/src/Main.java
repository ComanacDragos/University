import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        //Settings.tasks = 5;
        //splitTasks(6, 4).forEach(System.out::println);

        MatrixRepo matrixRepo;
        if(Settings.generateMatrix)
            matrixRepo = new MatrixRepo(
                new Matrix(Settings.al,Settings.ac, "data/a.txt"),
                new Matrix(Settings.bl, Settings.bc, "data/a.txt")
            );
        else
            matrixRepo = new MatrixRepo(
                    new Matrix("data/a.txt", Settings.al,Settings.ac),
                    new Matrix("data/a.txt", Settings.bl, Settings.bc)
            );

        List<Integer> tasks = Arrays.asList(1, 2, 4, 8, 16);
        List<Integer> poolThreads = Arrays.asList(0, 2, 4, 8);
        poolThreads.forEach(
                noPoolThreads->{
                    Settings.threadPoolSize = noPoolThreads;
                    tasks.forEach(noTasks ->{
                        Settings.tasks = noTasks;
                        double mean = 0.0;
                        for (int i = 0; i < 10; i++) {
                            if(Settings.threadPoolSize == 0)
                                mean += testThreads(matrixRepo);
                            else
                                mean += testThreadPool(matrixRepo);
                        }
                        Logger.log(mean/10.0);
                    });
                }
        );
    }

    public static double testThreads(MatrixRepo repo){
        List<List<MatrixEntry>> split = splitTasks(Settings.al, Settings.bc);
        List<Worker> workers = new LinkedList<>();
        split.forEach(subSplit-> workers.add(new Worker(repo, subSplit)));
        if(workers.size() != Settings.tasks)
            throw new RuntimeException("Bad number of workers");
        long start = System.currentTimeMillis();
        workers.forEach(Thread::start);
        workers.forEach(worker -> {
            try {
                worker.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        long time = System.currentTimeMillis() - start;
        return time/1000.0;
        //Logger.log(time/1000.0);
        //System.out.println(repo.getResults());
    }

    public static double testThreadPool(MatrixRepo repo){
        long start = System.currentTimeMillis();
        ExecutorService executorService = Executors.newFixedThreadPool(Settings.threadPoolSize);
        splitTasks(Settings.al, Settings.bc)
                .forEach(split->executorService.submit(new Task(repo, split)));
        executorService.shutdown();
        return (System.currentTimeMillis() - start)/1000.0;
    }

    public static List<List<MatrixEntry>> splitTasks(Integer lines, Integer columns){
        int elements = lines * columns;
        int chunk = elements / Settings.tasks;
        int rest = elements % Settings.tasks;
        List<List<MatrixEntry>> split = new LinkedList<>();
        List<MatrixEntry> subSplit = new LinkedList<>();
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                if(split.size() != Settings.tasks) {
                    subSplit.add(new MatrixEntry(i, j));
                    if(subSplit.size() == chunk){
                        split.add(subSplit);
                        subSplit = new LinkedList<>();
                    }
                }else {
                    split.get(--rest).add(new MatrixEntry(i, j));
                }
            }
        }
        return split;
    }
}
