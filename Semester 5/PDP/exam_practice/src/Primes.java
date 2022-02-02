import mpi.MPI;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;


public class Primes {
    static boolean isPrime(int n){
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

    public static void run(){
        int rank = MPI.COMM_WORLD.Rank();
        int nrProcs = MPI.COMM_WORLD.Size();
        System.out.println(rank + "/" + nrProcs);
        if(rank == 0){
            int maxN = 100;
            List<Integer> primesToSqrtN = new ArrayList<>();
            primesToSqrtN.add(2);
            for(int d=3;d*d<maxN;d+=2){
                if(isPrime(d))
                    primesToSqrtN.add(d);
            }
            primes(maxN, nrProcs, primesToSqrtN.stream().mapToInt(Integer::intValue).toArray())
                    .stream()
                    .sorted()
                    .forEach(System.out::println);
        }else{
            worker(rank, nrProcs);
        }
    }

    static List<Integer> findPrimes(int myId, int nrProcs, int maxN, int[] primesToSqrtN){
        List<Integer> result = new LinkedList<>();
        int last = primesToSqrtN[primesToSqrtN.length-1];
        int begin = myId * (maxN+1-last)/nrProcs + last;
        int end = (myId + 1) * (maxN+1-last)/nrProcs + last;
        for(int candidate = begin; candidate<end;candidate++){
            int i=0;
            while(i<primesToSqrtN.length && candidate%primesToSqrtN[i] != 0)
                i++;
            if(i==primesToSqrtN.length)
                result.add(candidate);
        }
        return result;
    }

    static List<Integer> primes(int maxN, int nrProcs, int[] primesToSqrtN){
        MPI.COMM_WORLD.Bcast(new int[]{maxN, primesToSqrtN.length}, 0, 2, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(primesToSqrtN, 0, primesToSqrtN.length, MPI.INT, 0);

        List<Integer> result = new LinkedList<>(findPrimes(0, nrProcs, maxN, primesToSqrtN));
        for(int prime: primesToSqrtN)
            result.add(prime);
        for(int i=1;i<nrProcs;i++){
            int[] size = new int[1];
            MPI.COMM_WORLD.Recv(size, 0, 1, MPI.INT, i, 0);
            int[] primes = new int[size[0]];
            MPI.COMM_WORLD.Recv(primes, 0, size[0], MPI.INT, i, 0);
            for(int prime: primes){
                result.add(prime);
            }
        }
        return result;
    }

    static void worker(int myId, int nrProcs){
        int[] sizes = new int[2];
        int maxN;
        MPI.COMM_WORLD.Bcast(sizes, 0, 2, MPI.INT, 0);
        maxN = sizes[0];
        int[] primesToSqrtN = new int[sizes[1]];
        MPI.COMM_WORLD.Bcast(primesToSqrtN, 0, sizes[1], MPI.INT, 0);
        List<Integer> result = new LinkedList<>(findPrimes(myId, nrProcs, maxN, primesToSqrtN));
        MPI.COMM_WORLD.Send(new int[]{result.size()},0,1,MPI.INT, 0, 0);
        MPI.COMM_WORLD.Send(result.stream().mapToInt(Integer::intValue).toArray(), 0, result.size(), MPI.INT, 0, 0);
    }
}
