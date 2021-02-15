package Model.ADTs;

import Exceptions.MyException;

import java.util.Iterator;
import java.util.stream.Stream;

public interface MyIStack<T> extends Iterable<T>{
    T pop() throws MyException;

    void push(T element);

    T peek() throws MyException;

    Boolean isEmpty();

    Iterator<T> iterator();

    Stream<T> stream();
}
