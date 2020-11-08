package Model.ADTs;

import Exceptions.MyException;

import java.util.Iterator;
import java.util.stream.Stream;

public interface MyIList<T> extends Iterable<T>{
    void add(T element);

    T pop() throws MyException;

    void clear();

    int size();

    boolean isEmpty();

    Iterator<T> iterator();

    Stream<T> stream();
}
