package Model.ADTs;

import Exceptions.EmptyCollection;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.stream.Stream;

public class MyList<T> implements MyIList<T>{
    LinkedList<T> list;
    ReadWriteLock readWriteLock = new ReentrantReadWriteLock();

    public MyList(){
        this.list = new LinkedList<>();
    }

    @Override
    public void add(T element) {
        this.readWriteLock.writeLock().lock();
        this.list.addLast(element);
        this.readWriteLock.writeLock().unlock();
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
    public Iterator<T> iterator() {
        return this.list.iterator();
    }

    @Override
    public Stream<T> stream() {
        return this.list.stream();
    }

    @Override
    public String toString() {
        if(this.list.isEmpty())
            return "";

        StringBuilder builder = new StringBuilder();
        for(T item : this.list){
            builder.append(item.toString()).append('\n');
        }
        return builder.toString();
    }
}
