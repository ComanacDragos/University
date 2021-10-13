import java.util.List;

public class Consumer extends Thread{
    Buffer buffer;
    Integer noNumbers;
    Integer sum = 0;

    public Consumer(Buffer buffer, Integer noNumbers) {
        this.buffer = buffer;
        this.noNumbers = noNumbers;
    }

    @Override
    public void run(){
       for(int i=0;i<noNumbers;i++){
          sum += buffer.take();
       }
        System.out.println("Computed sum is: " + sum);
    }
}
