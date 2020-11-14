package Model.ADTs;

import Exceptions.EmptyCollection;
import Exceptions.InexistentKey;

import java.util.Collection;
import java.util.Map;
import java.util.Set;
import java.util.stream.Stream;

public interface MyIDictionary<Key, Value> {
    void put(Key key, Value value);

    Value lookup(Key key);

    Value remove(Key key)throws EmptyCollection;

    void clear();

    int size();

    boolean isDefined(Key key);

    void update(Key key, Value value) throws InexistentKey;

    Set<Key> keySet();

    Collection<Value> values();

    void setContent(Map<Key, Value> newContent);

    Map<Key, Value> getContent();

    Stream<Map.Entry<Key, Value>> stream();
}
