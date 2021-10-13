import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Buffer {
    final Lock lock = new ReentrantLock();
    final Condition notFull = lock.newCondition();
    final Condition notEmpty = lock.newCondition();

    final Integer[] numbers = new Integer[Settings.bufferSize];
    int putPosition, takePosition, numberCount;

    public void put(Integer number){
        lock.lock();
        try{
            while (numberCount == numbers.length) // while the buffer is full wait
                notFull.await();
            numbers[putPosition] = number;
            putPosition++;
            if(putPosition == numbers.length)
                putPosition = 0;
            numberCount++;
            notEmpty.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }finally {
            lock.unlock();
        }
    }

    public Integer take(){
        lock.lock();
        try{
            while (numberCount == 0) // while the buffer is empty wait
                notEmpty.await();
            Integer number = numbers[takePosition];
            takePosition++;
            if(takePosition == numbers.length)
                takePosition = 0;
            numberCount--;
            notFull.signal();
            return number;
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }finally {
            lock.unlock();
        }
    }
}
