package Model.ADTs;

import Exceptions.EmptyCollection;
import java.util.LinkedList;

public class MyList<T> implements MyIList<T>{
    LinkedList<T> list;

    public MyList(){
        this.list = new LinkedList<>();
    }

    @Override
    public void add(T element) {
        this.list.addLast(element);
    }

    @Override
    public T pop() throws EmptyCollection {
        if(this.list.isEmpty())
            throw new EmptyCollection("Empty list");
        return this.list.removeFirst();
    }

    @Override
    public void clear() {
        this.list.clear();
    }

    @Override
    public int size() {
        return this.list.size();
    }

    @Override
    public boolean isEmpty() {
        return this.list.isEmpty();
    }

    @Override
    public String toString() {
        if(this.list.isEmpty())
            return "|";

        StringBuilder builder = new StringBuilder();
        for(T item : this.list){
            builder.append(item.toString()).append(" | ");
        }
        return builder.toString();
    }
}
