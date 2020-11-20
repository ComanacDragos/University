package Model.ADTs;

import Model.Values.IValue;

import java.util.concurrent.atomic.AtomicInteger;

public class MyHeap extends MyDictionary<Integer, IValue>{
    AtomicInteger address;

    public MyHeap() {
        super();
        this.address = new AtomicInteger(0);
    }

    public Integer put(IValue value) {
        int newAddress = this.address.incrementAndGet();
        super.put(newAddress, value);
        return newAddress;
    }
}
