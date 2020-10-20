package Model.ADTs;

import Exceptions.EmptyCollection;

public interface MyIList<T> {
    void add(T element);

    T pop() throws EmptyCollection;

    void clear();

    int size();

    boolean isEmpty();
}
