package Model.ADTs;

import Exceptions.MyException;

public interface MyIList<T> {
    void add(T element);

    T get(int position) throws MyException;

    void set(int position, T element) throws MyException;

    void remove(int position) throws MyException;

    void clear();

    int size();
}
