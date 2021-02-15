package Model.ADTs;

import Exceptions.EmptyCollection;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.stream.Stream;

public class MyList<T> implements MyIList<T>{
    final LinkedList<T> list;
    public MyList(){
        this.list = new LinkedList<>();
    }

    @Override
    public void add(T element) {
        synchronized (this.list) {
            this.list.addLast(element);
        }
    }

    @Override
    public T pop() throws EmptyCollection {
        synchronized (this.list) {
            if (this.list.isEmpty())
                throw new EmptyCollection("Empty list");
            return this.list.removeFirst();
        }
    }

    @Override
    public void clear() {
        synchronized (this.list) {
            this.list.clear();
        }
    }

    @Override
    public int size() {
        synchronized (this.list) {
            return this.list.size();
        }
    }

    @Override
    public boolean isEmpty() {
        synchronized (this.list) {
            return this.list.isEmpty();
        }
    }

    @Override
    public Iterator<T> iterator() {
        synchronized (this.list) {
            return this.list.iterator();
        }
    }

    @Override
    public Stream<T> stream() {
        synchronized (this.list) {
            return this.list.stream();
        }
    }

    @Override
    public String toString() {
        synchronized (this.list) {
            if (this.list.isEmpty())
                return "";

            StringBuilder builder = new StringBuilder();
            for (T item : this.list) {
                builder.append(item.toString()).append('\n');
            }
            return builder.toString();
        }
    }
}
