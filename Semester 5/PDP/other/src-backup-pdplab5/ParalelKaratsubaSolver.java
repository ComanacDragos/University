import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class ParalelKaratsubaSolver {

    public static Polynomial multiply(Polynomial p, Polynomial q, Integer noThreads){
        Worker worker = new Worker(p, q, noThreads);

        return worker.call();
    }

    private static class Worker implements Callable<Polynomial> {
        Polynomial p, q;
        Integer noThreads;

        static AtomicInteger activeThreads = new AtomicInteger(0);

        public Worker(Polynomial p, Polynomial q, Integer noThreads) {
            this.p = p;
            this.q = q;
            activeThreads.incrementAndGet();
            this.noThreads = noThreads;
        }

        @Override
        public Polynomial call(){
            Polynomial result = null;
            try {
                if(activeThreads.get() >= noThreads) {
                    return SequentialKaratsubaMultiplier.multiply(p, q);
                }

                int n = (p.getDegree()+1)/2;
                //Polynomial result = new Polynomial(n+n-1);
                Polynomial p1 = new PolynomialCopy(p, 0, n);
                Polynomial p2 = new PolynomialCopy(p, n, p.getDegree());

                Polynomial q1 = new PolynomialCopy(q, 0, n);
                Polynomial q2 = new PolynomialCopy(q, n, p.getDegree());

                Polynomial p1q1, p2q2, middle;

                Future<Polynomial> p1q1Future, p2q2Future, middleFuture;

                ExecutorService executorService = Executors.newCachedThreadPool();
                p1q1Future = executorService.submit(new Worker(p1, q1, noThreads));
                p2q2Future = executorService.submit(new Worker(p2, q2, noThreads));

                middleFuture = executorService.submit(new Worker(SequentialAdder.add(p1, p2, 1),
                        SequentialAdder.add(q1, q2, 1), noThreads));

                executorService.shutdown();

                p1q1 = p1q1Future.get();
                p2q2 = p2q2Future.get();
                middle = middleFuture.get();

                executorService.awaitTermination(1, TimeUnit.MILLISECONDS);

                result = new PolynomialImpl(p.getDegree() + q.getDegree() - 1);
                for(int i=0;i<p.getDegree()+q.getDegree()-1;i++){
                    if(i<p1q1.getDegree()){
                        result.accumulate(i, p1q1.get(i));
                    }
                    if(n<=i && i<middle.getDegree()+n) {
                        int s = middle.get(i-n);
                        if(i-n<p1q1.getDegree())
                            s-= p1q1.get(i-n);
                        if(i-n<p2q2.getDegree())
                            s-= p2q2.get(i-n);
                        result.accumulate(i, s);
                    }
                    if(2*n<=i && i<p2q2.getDegree()+2*n){
                        result.accumulate(i, p2q2.get(i-2*n));
                    }
                }
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
            return result;
        }
    }
}
