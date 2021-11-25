public class ParalelKaratsubaSolver {
    public static Polynomial multiply(Polynomial p, Polynomial q, Integer noThreads){
        Worker worker = new Worker(p, q,noThreads);
        worker.run();
        return worker.result;
    }

    private static class Worker extends Thread{
        Polynomial p, q, result;
        Integer noThreads;

        public Worker(Polynomial p, Polynomial q, Integer noThreads) {
            this.p = p;
            this.q = q;
            this.noThreads = noThreads-1;
        }

        @Override
        public void run(){
            try {
                int n = (p.degree+1)/2;
                //Polynomial result = new Polynomial(n+n-1);
                Polynomial p1 = new Polynomial(p, 0, n);
                Polynomial p2 = new Polynomial(p, n, p.degree);

                Polynomial q1 = new Polynomial(q, 0, n);
                Polynomial q2 = new Polynomial(q, n, p.degree);

                Polynomial p1q1, p2q2, middle;

                if(noThreads == 0 || (p1.degree < 6 && p2.degree < 6 && q1.degree < 6 && q2.degree < 6)) {
                    p1q1 = SequentialRegularMultiplier.multiply(p1, q1);
                    p2q2 = SequentialRegularMultiplier.multiply(p2, q2);

                    middle = SequentialKaratsubaMultiplier.multiply(
                            SequentialAdder.add(p1, p2, 1),
                            SequentialAdder.add(q1, q2, 1)
                    );
                }else{

                    if(noThreads == 1){
                        p1q1 = SequentialKaratsubaMultiplier.multiply(p1, q1);
                        Worker worker = new Worker(p2, q2, 1);
                        worker.start();

                        middle = SequentialKaratsubaMultiplier.multiply(
                                SequentialAdder.add(p1, p2, 1),
                                SequentialAdder.add(q1, q2, 1)
                        );
                        worker.join();
                        p2q2 = worker.result;
                    }else{
                        Worker workerP1q1 = new Worker(p1, q1, noThreads/2);
                        workerP1q1.start();
                        Worker workerP2q2 = new Worker(p2, q2, noThreads - noThreads/2);
                        workerP2q2.start();

                        middle = SequentialKaratsubaMultiplier.multiply(
                                SequentialAdder.add(p1, p2, 1),
                                SequentialAdder.add(q1, q2, 1)
                        );
                        workerP1q1.join();
                        p1q1 = workerP1q1.result;
                        workerP2q2.join();
                        p2q2 = workerP2q2.result;
                    }
                }
                middle = SequentialAdder.add(middle, p1q1, -1);
                middle = SequentialAdder.add(middle, p2q2, -1);

                result = new Polynomial(p.degree + q.degree - 1);
                for(int i=0;i<p.degree+q.degree-1;i++){
                    if(i<p1q1.degree){
                        result.accumulate(i, p1q1.get(i));
                    }
                    if(n<=i && i<middle.degree+n) {
                        result.accumulate(i, middle.get(i - n));
                    }
                    if(2*n<=i && i<p2q2.degree+2*n){
                        result.accumulate(i, p2q2.get(i-2*n));
                    }
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
