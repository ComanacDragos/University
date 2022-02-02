import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

public class Primes {
    List<Integer> primesToSqrtN = new ArrayList<>();
    final List<Integer> allPrimes = new ArrayList<>();

    boolean isPrime(int n){
        if(n==2)
            return true;
        if(n%2==0 || n<2){
            return false;
        }
        for(int d = 3; d*d<=n; d+=2){
            if(n%d == 0)
                return false;
        }
        return true;
    }
    public void run() {
        int maxN = 100;
        int noThreads = 4;
        List<Thread> threads = new LinkedList<>();
        primesToSqrtN.add(2);
        for(int d=3;d*d<maxN;d+=2){
            if(isPrime(d))
                primesToSqrtN.add(d);
        }
        int last = primesToSqrtN.get(primesToSqrtN.size()-1);
        for(int i=0;i<4;i++){
            int start = i * (maxN-last + noThreads-1)/noThreads;
            int end =  (i+1) * (maxN-last + noThreads-1)/noThreads;

            start += last+1;
            end += last+1;
            if(end>maxN+1){
                end = maxN+1;
            }
            Thread t = new Worker(start,end);
            t.start();
            threads.add(t);
        }
        threads.forEach(t->{
            try{
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        allPrimes.addAll(primesToSqrtN);
        allPrimes.stream().sorted(Comparator.comparingInt(a -> a)).forEach(System.out::println);
    }

    public class Worker extends Thread{
        int start, end;
        Worker(int start, int end){
            this.start = start;
            this.end = end;
        }

        @Override
        public void run(){
            System.out.println(Thread.currentThread().getId() + ". Starting: " + start + " -> " + end);
            List<Integer> localPrimes = new LinkedList<>();
            for(int i=start;i<end;i++){
                boolean isPrime = true;
                for(int prime: primesToSqrtN)
                    if(i%prime == 0){
                        isPrime = false;
                        break;
                    }
                if(isPrime){
                    localPrimes.add(i);
                }
            }
            synchronized (allPrimes){
                allPrimes.addAll(localPrimes);
            }
        }
    }
}
