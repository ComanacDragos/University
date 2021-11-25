import java.util.*;

public class ParalelRegularSolver {
    public static Polynomial multiply(Polynomial p, Polynomial q, Integer noThreads, List<List<Integer>> splitTasks){
        Thread[] threads = new Thread[noThreads];

        PolynomialImpl result = new PolynomialImpl(p.getDegree()+q.getDegree()-1);

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
            subSplit.add(i);
            if(subSplit.size() == chunk){
                if(rest > 0){
                    rest--;
                    i++;
                    subSplit.add(i);
                }
                split.add(subSplit);
                subSplit = new LinkedList<>();
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
                if(position < p.getDegree())
                    end = position;
                else
                    end = p.getDegree()-1;
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

// 0 1 2 3 4 -- 5
// 0 1 2 3 4 -- 5

// 0 1 2 3 4 5 6 7 8
/*
0 -> 0,0
1 -> 0,1 1,0
2 -> 0,2 1,1 2,0
3 -> 0,3 1,2 2,1, 3,0
4  -> 0,4 1,3 2,2 3,1, 4,0
5 -> 1,4 2,3 3,2, 4,1
6 -> 2,4 3,3, 4,2
7 -> 3,4 4,3
8 -> 4,4

0 1 2
0 1 2

0 1 2 3 4

0 -> 0,0
1 -> 0,1 1,0
2 -> 0,2 1,1 2,0
3 -> 1,2 2,1
4 -> 2,2



 */
