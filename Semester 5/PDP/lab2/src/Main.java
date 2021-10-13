import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        List<Integer> firstList = Arrays.asList(1,2,3,4,5);
        List<Integer> secondList = Arrays.asList(1,2,3,4,5);

        // 1 + 4
        //Random rand = new Random();

        int trueSum = 0;
        for(int i=0;i<5;i++){
            //firstList.add(rand.nextInt());
            //secondList.add(rand.nextInt());

            trueSum += firstList.get(i) * secondList.get(i);
        }
        System.out.println("True sum: " + trueSum);

        Buffer buffer = new Buffer();
        Producer producer = new Producer(firstList, secondList, buffer);
        Consumer consumer = new Consumer(buffer, Settings.noNumbers);

        producer.start();
        consumer.start();

        producer.join();
        consumer.join();

    }
}
