package Model.adt;

import java.util.LinkedList;
import java.util.Queue;

public class List<T> implements IList<T> {
    Queue<T> list;

    @Override
    public void add(T v) { }

    @Override
    public T pop() {return list.poll();}

}
