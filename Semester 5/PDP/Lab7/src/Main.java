import mpi.MPI;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;


public class Main {
    public static String P = "E:\\University\\Semester 5\\PDP\\Lab7\\data\\p1.txt";
    public static String Q = "E:\\University\\Semester 5\\PDP\\Lab7\\data\\p2.txt";

    public static int rank, processes;
    public static boolean enableLogs = true;
    public static String variant = "regularMPI";


    public static void main(String[] args) {
        MPI.Init(args);
        rank = MPI.COMM_WORLD.Rank();
        processes = MPI.COMM_WORLD.Size();

        log("out of " + processes);
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
            log("Check: " + SequentialRegularMultiplier.multiply(p, q));

            if(variant.equals("regularMPI"))
                runRegularMaster(p, q);
            else
                runKaratsubaMaster(p, q);

        }else{
            Polynomial p = new Polynomial(receiveArray(0));
            Polynomial q = new Polynomial(receiveArray(0));

            if(variant.equals("regularMPI"))
                runRegularWorker(p, q);
            else
                runKaratsubaWorker(p, q);
        }
        MPI.Finalize();
    }

    public static void runKaratsubaMaster(Polynomial p, Polynomial q) {
        int[] freeProcesses = new int[processes-1];
        for(int i=1;i<processes;i++)
            freeProcesses[i-1] = i;
        runKaratsuba(p, q, freeProcesses);
    }

    public static void runKaratsubaWorker(Polynomial p, Polynomial q){
        runKaratsuba(p, q, receiveArray(MPI.ANY_SOURCE));
    }

    public static void  runKaratsuba(Polynomial p, Polynomial q, int[] freeProcesses){

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
