package Model.ADTs;

import Exceptions.MyException;

public interface MyIDictionary<Key, Value> {
    void put(Key key, Value value);

    Value get(Key key);

    void remove(Key key)throws MyException;

    void clear();

    int size();
}
