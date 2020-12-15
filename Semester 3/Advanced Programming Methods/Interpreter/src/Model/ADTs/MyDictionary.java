package Model.ADTs;

import Exceptions.EmptyCollection;
import Exceptions.InexistentKey;
import Exceptions.MyException;


import java.util.Collection;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Stream;

public class MyDictionary<Key, Value> implements MyIDictionary<Key, Value>{
    final Map<Key, Value> dictionary;

    public MyDictionary(){
        this.dictionary = new ConcurrentHashMap<>();
    }

    @Override
    public void put(Key key, Value value) {
        this.dictionary.put(key, value);
    }

    @Override
    public Value lookup(Key key) {
        Value value = this.dictionary.get(key);
        if(Objects.nonNull(value)){
            return value;
        }
        throw new MyException(key + " is not a key");
    }

    @Override
    public Value remove(Key key) throws EmptyCollection {
        synchronized(this.dictionary) {
            if (this.dictionary.isEmpty())
                throw new EmptyCollection("Empty dictionary");
            return this.dictionary.remove(key);
        }
    }

    @Override
    public void clear() {
        this.dictionary.clear();
    }

    @Override
    public int size() {
        return this.dictionary.size();
    }

    @Override
    public boolean isDefined(Key key) {
        return this.dictionary.containsKey(key);
    }

    @Override
    public void update(Key key, Value value) throws InexistentKey {
        synchronized (this.dictionary) {
            if (this.dictionary.containsKey(key))
                this.dictionary.put(key, value);
            else
                throw new InexistentKey(key.toString() + " key does not exist");
        }
    }

    @Override
    public Set<Key> keySet() {
        return this.dictionary.keySet();
    }

    @Override
    public Collection<Value> values() {
        return this.dictionary.values();
    }

    @Override
    public void setContent(Map<Key, Value> newContent) {
        synchronized (this.dictionary) {
            this.dictionary.clear();

            newContent.forEach(this.dictionary::put);
        }
    }

    @Override
    public Map<Key, Value> getContent() {
        return this.dictionary;
    }

    @Override
    public Stream<Map.Entry<Key, Value>> stream() {
        return this.dictionary.entrySet().stream();
    }

    @Override
    public MyIDictionary<Key, Value> shallowCopy() {
        MyIDictionary<Key, Value> shallowCopy = new MyDictionary<>();

        this.dictionary.forEach(shallowCopy::put);

        return shallowCopy;
    }

    @Override
    public String toString() {
        synchronized (this.dictionary) {
            if (this.dictionary.isEmpty())
                return "";

            StringBuilder builder = new StringBuilder();

            for (Key key : this.dictionary.keySet())
                builder.append(key.toString()).append(" -> ").append(this.dictionary.get(key)).append('\n');
            return builder.toString();
        }
    }
}
