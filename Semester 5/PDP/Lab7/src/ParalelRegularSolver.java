import java.util.LinkedList;
import java.util.List;

public class ParalelRegularSolver {
    public static Polynomial multiply(Polynomial p, Polynomial q, Integer noThreads, List<List<Integer>> splitTasks){
        Thread[] threads = new Thread[noThreads];

        Polynomial result = new Polynomial(p.degree+q.degree-1);

        try{
            for(int i=0;i<noThreads;i++){
                threads[i] = new Worker(splitTasks.get(i), p, q, result);
                threads[i].start();
            }
            for (int i=0;i<noThreads;i++)
                threads[i].join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return result;
    }

    public static List<List<Integer>> splitTasks(Integer pDegree, Integer qDegree, Integer noThreads){
        int elements = pDegree + qDegree-1;
        int chunk = elements / noThreads;
        int rest = elements % noThreads;
        List<List<Integer>> split = new LinkedList<>();
        List<Integer> subSplit = new LinkedList<>();
        for (int i = 0; i < elements; i++) {
           if(split.size() != noThreads) {
                subSplit.add(i);
                if(subSplit.size() == chunk){
                    split.add(subSplit);
                    subSplit = new LinkedList<>();
                }
            }else {
                split.get(--rest).add(i);
            }
        }
        return split;
    }

    private static class Worker extends Thread{
        List<Integer> tasks;
        Polynomial p, q, result;

        public Worker(List<Integer> tasks, Polynomial p, Polynomial q, Polynomial result) {
            this.tasks = tasks;
            this.p = p;
            this.q = q;
            this.result = result;
        }

        @Override
        public void run(){
            for(Integer position : tasks){
                int s = 0;
                int start, end;
                if(position < p.degree)
                    end = position;
                else
                    end = p.degree-1;
                start = position - end;
                if(start < 0)
                    start = 0;
                for(int i=start;i<=end;i++) {
                    s += p.get(i) * q.get(position - i);
                }
                result.set(position, s);
            }
        }
    }
}
