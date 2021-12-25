import mpi.MPI;
import mpi.Status;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;


public class Main {
    public static String P = "E:\\University\\Semester 5\\PDP\\Lab7\\data\\p1.txt";
    public static String Q = "E:\\University\\Semester 5\\PDP\\Lab7\\data\\p2.txt";

    public static int rank, processes;
    public static boolean enableLogs = true;
    public static String variant = "kregularMPI";

    public static void main(String[] args) {
        MPI.Init(args);
        rank = MPI.COMM_WORLD.Rank();
        processes = MPI.COMM_WORLD.Size();
        //if(rank == 0)
        //generatePolynomials(20, 20);
        run();
        MPI.Finalize();
    }

    public static void run(){
        log("out of " + processes + " - " + variant);
        if(variant.equals("regularMPI"))
            runRegular();
        else
            runKaratsuba();
    }

    public static void runRegular(){
        if(rank == 0){
            Polynomial p = new Polynomial(P);
            for(int i=1;i<processes;i++){
                sendArray(p.coefficients, i);
            }
            Polynomial q = new Polynomial(Q);
            for(int i=1;i<processes;i++){
                sendArray(q.coefficients, i);
            }
            log(p);
            log(q);
            //log("Check: " + SequentialRegularMultiplier.multiply(p, q));
            runRegularMaster(p, q);
        }else{
            Polynomial p = new Polynomial(receiveArray(0));
            Polynomial q = new Polynomial(receiveArray(0));
            runRegularWorker(p, q);
        }
    }

    public static void runKaratsuba(){
        if(rank == 0 ){
            Polynomial p = new Polynomial(P);
            Polynomial q = new Polynomial(Q);
            log(p);
            log(q);
            log("Check: " + SequentialRegularMultiplier.multiply(p, q));
            runKaratsubaMaster(p, q);
        }else{
            runKaratsubaWorker();
        }
    }

    public static void runKaratsubaMaster(Polynomial p, Polynomial q) {
        int[] freeProcesses = new int[processes-1];
        for(int i=1;i<processes;i++)
            freeProcesses[i-1] = i;
        log("Initial free processes: " + Arrays.toString(freeProcesses));
        Polynomial result = runKaratsuba(p, q, freeProcesses);
        log("Result: " + result);
    }

    public static void runKaratsubaWorker(){
        int[] firstArray = receiveArray(MPI.ANY_SOURCE);
        if(firstArray.length == 0) {
            log("received end message, finishing...");
            return;
        }
        Polynomial p = new Polynomial(firstArray);
        Polynomial q = new Polynomial(receiveArray(MPI.ANY_SOURCE));
        int[] len = new int[1];
        MPI.COMM_WORLD.Recv(len, 0, 1, MPI.INT, MPI.ANY_SOURCE, 0);
        int [] freeProcesses = new int[len[0]];
        Status status = MPI.COMM_WORLD.Recv(freeProcesses, 0, freeProcesses.length, MPI.INT, MPI.ANY_SOURCE, 0);
        log("Received: " + freeProcesses.length + " -> " + Arrays.toString(freeProcesses));
        Polynomial result = runKaratsuba(p, q, freeProcesses);
        sendArray(result.coefficients, status.source);
    }

    public static Polynomial runKaratsuba(Polynomial p, Polynomial q, int[] freeProcesses){
        int n = (p.degree+1)/2;
        Polynomial p1 = new Polynomial(p, 0, n);
        Polynomial p2 = new Polynomial(p, n, p.degree);

        Polynomial q1 = new Polynomial(q, 0, n);
        Polynomial q2 = new Polynomial(q, n, p.degree);

        Polynomial p1q1, p2q2, middle;

        if(freeProcesses.length == 0 || (p1.degree < 6 && p2.degree < 6 && q1.degree < 6 && q2.degree < 6)) {
            p1q1 = SequentialRegularMultiplier.multiply(p1, q1);
            p2q2 = SequentialRegularMultiplier.multiply(p2, q2);

            middle = SequentialKaratsubaMultiplier.multiply(
                    SequentialAdder.add(p1, p2, 1),
                    SequentialAdder.add(q1, q2, 1)
            );
            if(freeProcesses.length > 0){
                for(int i=0;i<freeProcesses.length;i++)
                    sendArray(new int[0], freeProcesses[i]);
            }
        }else{
            if(freeProcesses.length == 1){
                p1q1 = SequentialKaratsubaMultiplier.multiply(p1, q1);
                sendArray(p2.coefficients, freeProcesses[0]);
                sendArray(q2.coefficients, freeProcesses[0]);
                sendArray(new int[0], freeProcesses[0]);

                middle = SequentialKaratsubaMultiplier.multiply(
                        SequentialAdder.add(p1, p2, 1),
                        SequentialAdder.add(q1, q2, 1)
                );
                p2q2 = new Polynomial(receiveArray(freeProcesses[0]));
            }else{
                int[] remainingFirst = new int[(freeProcesses.length-2)/2];
                int[] remainingSecond = new int[freeProcesses.length-2 - (freeProcesses.length-2)/2];
                System.arraycopy(freeProcesses, 2, remainingFirst, 0, remainingFirst.length);
                //log(Arrays.toString(remainingFirst));
                System.arraycopy(freeProcesses, 2+remainingFirst.length, remainingSecond, 0, remainingSecond.length);
                log(Arrays.toString(freeProcesses) + " -> " + Arrays.toString(remainingFirst) + " + " + Arrays.toString(remainingSecond));

                sendArray(p1.coefficients, freeProcesses[0]);
                sendArray(q1.coefficients, freeProcesses[0]);
                sendArray(remainingFirst, freeProcesses[0]);

                sendArray(p2.coefficients, freeProcesses[1]);
                sendArray(q2.coefficients, freeProcesses[1]);
                sendArray(remainingSecond, freeProcesses[1]);

                middle = SequentialKaratsubaMultiplier.multiply(
                        SequentialAdder.add(p1, p2, 1),
                        SequentialAdder.add(q1, q2, 1)
                );
                p1q1 = new Polynomial(receiveArray(freeProcesses[0]));
                p2q2 = new Polynomial(receiveArray(freeProcesses[1]));
            }
        }
        middle = SequentialAdder.add(middle, p1q1, -1);
        middle = SequentialAdder.add(middle, p2q2, -1);

        Polynomial result = new Polynomial(p.degree + q.degree - 1);
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
        return result;
    }

    public static void runRegularMaster(Polynomial p, Polynomial q){
        List<List<Integer>> splits = splitTasks(p.degree, q.degree, processes-1);
        for(int i=1;i<processes;i++){
            sendArray(splits.get(i-1).stream().mapToInt(Integer::intValue).toArray(), i);
        }
        int[] result = new int[p.degree + q.degree - 1];
        for(int i=1;i<processes;i++){
            int[] partialResult = receiveArray(i);
            List<Integer> split = splits.get(i-1);
            for(int j=0;j<split.size();j++){
                result[split.get(j)] = partialResult[j];
            }
        }
        log("Result: " + new Polynomial(result));
    }

    public static void runRegularWorker(Polynomial p, Polynomial q){
        int[] positions = receiveArray(0);
        int[] result = new int[positions.length];
        for(int j=0;j<positions.length;j++){
            int position = positions[j];
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
            result[j] = s;
        }
        sendArray(result, 0);
    }

    public static void sendArray(int[] array, int process){
        MPI.COMM_WORLD.Send(new int[]{array.length}, 0, 1, MPI.INT, process, 0);
        MPI.COMM_WORLD.Send(array, 0, array.length, MPI.INT, process, 0);
        log("Sent: " + Arrays.toString(array) + " to " + process);
    }

    public static int[] receiveArray(int process){
        int[] len = new int[1];
        MPI.COMM_WORLD.Recv(len, 0, 1, MPI.INT, process, 0);
        int [] array = new int[len[0]];
        MPI.COMM_WORLD.Recv(array, 0, array.length, MPI.INT, process, 0);
        log("Received: " + array.length + " -> " + Arrays.toString(array));
        return array;
    }

    public static void generatePolynomials(int degree1, int degree2){
        new Polynomial(degree1, P);
        new Polynomial(degree2, Q);
    }

    public static List<List<Integer>> splitTasks(Integer pDegree, Integer qDegree, Integer noProcesses){
        int elements = pDegree + qDegree-1;
        int chunk = elements / noProcesses;
        int rest = elements % noProcesses;
        List<List<Integer>> split = new ArrayList<>();
        List<Integer> subSplit = new ArrayList<>();
        for (int i = 0; i < elements; i++) {
            if(split.size() != noProcesses) {
                subSplit.add(i);
                if(subSplit.size() == chunk){
                    split.add(subSplit);
                    subSplit = new ArrayList<>();
                }
            }else {
                split.get(--rest).add(i);
            }
        }
        return split;
    }

    public static void log(Object message){
        if(enableLogs)
            System.out.println(rank + ". " + message);
    }
}
