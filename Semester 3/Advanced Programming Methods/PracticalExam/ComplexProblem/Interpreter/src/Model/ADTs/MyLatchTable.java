package Model.ADTs;

import Exceptions.MyException;

import java.util.concurrent.atomic.AtomicInteger;

public class MyLatchTable extends MyDictionary<Integer,Integer>{
    AtomicInteger freeLocation = new AtomicInteger(0);

    @Override
    public synchronized Integer lookup(Integer integer) {
        return super.lookup(integer);
    }

    public synchronized Integer put(Integer integer) {
        super.put(freeLocation.incrementAndGet(), integer);
        return freeLocation.get();
    }

    public synchronized void countDown(Integer latch){
        if(this.isDefined(latch)){
            Integer count = this.lookup(latch);
            if(count>0)
                this.update(latch, count-1);
        }else{
            throw new MyException("Latch does not exist");
        }
    }
}
