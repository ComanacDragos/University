package Model.ADTs;

import Exceptions.MyException;

public interface MyIDictionary<Key, Value> {
    void put(Key key, Value value);

    Value lookup(Key key);

    void remove(Key key)throws MyException;

    void clear();

    int size();

    boolean isDefined(Key key);

    void update(Key key, Value value);
}
