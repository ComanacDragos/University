import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;

public class ParalelKaratsubaSolver {
    public static Polynomial multiply(Polynomial p, Polynomial q, Integer noThreads){
        List<ReentrantLock> locks = new ArrayList<>();
        for(int i=0;i<p.degree+q.degree-1;i++)
            locks.add(new ReentrantLock());

        return null;
    }

    private static class Worker extends Thread{
        List<ReentrantLock> locks;
        List<Map.Entry<Integer, Integer>> tasks;
        Polynomial p, q, result;

        public Worker(List<ReentrantLock> locks, List<Map.Entry<Integer, Integer>> tasks, Polynomial p, Polynomial q) {
            this.locks = locks;
            this.tasks = tasks;
            this.p = p;
            this.q = q;
        }

        @Override
        public void run(){

        }
    }
}
