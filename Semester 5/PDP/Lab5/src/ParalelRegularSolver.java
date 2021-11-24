import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

public class ParalelRegularSolver {
    public static Polynomial multiply(Polynomial p, Polynomial q, Integer noThreads){
        List<ReentrantLock> locks = new ArrayList<>();
        for(int i=0;i<p.degree+q.degree-1;i++)
            locks.add(new ReentrantLock());
        Thread[] threads = new Thread[noThreads];

        Polynomial result = new Polynomial(p.degree+q.degree-1);

        List<List<Map.Entry<Integer, Integer>>> splitTasks = splitTasks(p.degree, q.degree, noThreads);
        try{
            for(int i=0;i<noThreads;i++){
                threads[i] = new Worker(locks, splitTasks.get(i), p, q, result);
                threads[i].start();
            }
            for (int i=0;i<noThreads;i++)
                threads[i].join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return result;
    }

    public static List<List<Map.Entry<Integer, Integer>>> splitTasks(Integer pDegree, Integer qDegree, Integer noThreads){
        int elements = pDegree * qDegree;
        int chunk = elements / noThreads;
        int rest = elements % noThreads;
        List<List<Map.Entry<Integer, Integer>>> split = new LinkedList<>();
        List<Map.Entry<Integer, Integer>> subSplit = new LinkedList<>();
        for (int i = 0; i < pDegree; i++) {
            for (int j = 0; j < qDegree; j++) {
                if(split.size() != noThreads) {
                    subSplit.add(Map.entry(i, j));
                    if(subSplit.size() == chunk){
                        split.add(subSplit);
                        subSplit = new LinkedList<>();
                    }
                }else {
                    split.get(--rest).add(Map.entry(i, j));
                }
            }
        }
        return split;
    }

    private static class Worker extends Thread{
        List<ReentrantLock> locks;
        List<Map.Entry<Integer, Integer>> tasks;
        Polynomial p, q, result;

        public Worker(List<ReentrantLock> locks, List<Map.Entry<Integer, Integer>> tasks, Polynomial p, Polynomial q, Polynomial result) {
            this.locks = locks;
            this.tasks = tasks;
            this.p = p;
            this.q = q;
            this.result = result;
        }

        @Override
        public void run(){
            for(Map.Entry<Integer, Integer> entry : tasks){
                int position = entry.getKey() + entry.getValue();
                int pValue = p.get(entry.getKey());
                int qValue = q.get(entry.getValue());
                locks.get(position).lock();
                result.accumulate(position, pValue * qValue);
                locks.get(position).unlock();
            }
        }
    }
}
