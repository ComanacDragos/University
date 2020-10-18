package Model.ADTs;

import Exceptions.EmptyCollection;
import Exceptions.MyException;

public interface MyIStack<T> {
    T pop() throws MyException, EmptyCollection;

    void push(T element);

    T peek() throws EmptyCollection;

    Boolean isEmpty();
}
