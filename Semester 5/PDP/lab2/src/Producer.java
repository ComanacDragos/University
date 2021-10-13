import java.util.LinkedList;
import java.util.List;

public class Producer extends Thread{
    List<Integer> firstList;
    List<Integer> secondList;
    Buffer buffer;

    public Producer(List<Integer> firstList, List<Integer> secondList, Buffer buffer) {
        this.firstList = firstList;
        this.secondList = secondList;
        this.buffer = buffer;

        if(firstList.size() != secondList.size())
            throw new RuntimeException("Sizes must be the same");
    }

    @Override
    public void run(){
        for(int i=0;i<firstList.size();i++){
            buffer.put(firstList.get(i) * secondList.get(i));
        }
    }

}
