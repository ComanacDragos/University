import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ParallelSolver extends Solver{
    ExecutorService executorService;
    Lock lock = new ReentrantLock();
    Integer activeTasks = 0, totalThreads;

    public ParallelSolver(DirectedGraph graph, Integer totalThreads) {
        super(graph);
        this.totalThreads = totalThreads;
        this.executorService = Executors.newFixedThreadPool(totalThreads);
    }

    @Override
    public void bkt(List<Integer> path) {
        path.add(0);
        path.add(0);
        for(int i=1;i<graph.getNoVertices();i++){
            path.set(path.size()-1, i);
            if(consistent(path)){
                if(solution(path)) {
                    lock.lock();
                    if(!solutions.contains(path))
                        solutions.add(new ArrayList<>(path));
                    lock.unlock();
                }
                else {
                    if(activeTasks < this.totalThreads) {
                        executorService.execute(new Worker(new ArrayList<>(path)));
                        activeTasks++;
                    }
                    else
                        break;
                }
            }
        }

        executorService.shutdown();
        try{
            if(!executorService.awaitTermination(1, TimeUnit.MINUTES))
                System.out.println("Terminated too early");
        }catch (InterruptedException e){
            e.printStackTrace();
        }
    }

    private class Worker implements Runnable {
        List<Integer> initialPath;

        public Worker(List<Integer> initialPath) {
            this.initialPath = initialPath;
        }

        @Override
        public void run(){
            //System.out.println(Thread.currentThread().getId() + " -- " + initialPath);
            worker_bkt(initialPath);
        }

        public void worker_bkt(List<Integer> path) {
            path.add(0);
            for(int i=0;i<graph.getNoVertices();i++){
                path.set(path.size()-1, i);
                //System.out.println(path);
                if(consistent(path)){
                    if(solution(path)) {
                        //System.out.println(Thread.currentThread().getId() + " -- " + path);
                        lock.lock();
                        if(!solutions.contains(path))
                            solutions.add(new ArrayList<>(path));
                        lock.unlock();
                    }
                    else {
                        worker_bkt(new ArrayList<>(path));
                    }
                }
            }
        }
    }
}
