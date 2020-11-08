package Model.ADTs;

import Exceptions.EmptyCollection;
import Exceptions.MyException;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;
import java.util.stream.Stream;


public class MyStack<T> implements MyIStack<T>{
    Deque<T> stack;

    public MyStack(){
        this.stack = new ArrayDeque<>() {
        };
    }

    @Override
    public T pop() throws MyException {
        if(this.stack.isEmpty())
            throw new EmptyCollection("Empty stack");
        return this.stack.pop();
    }

    @Override
    public void push(T element) {
        this.stack.push(element);
    }

    @Override
    public T peek() throws EmptyCollection {
        if(this.stack.isEmpty())
            throw new EmptyCollection("Empty stack");
        return this.stack.peek();
    }

    @Override
    public Boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public Iterator<T> iterator() {
        return this.stack.iterator();
    }

    @Override
    public Stream<T> stream() {
        return this.stack.stream();
    }

    @Override
    public String toString() {
        if(this.stack.isEmpty())
            return "";

        StringBuilder contents = new StringBuilder();

        for(T element : this.stack)
            contents.append("(\n").append(element.toString()).append("\n)\n");
        return contents.toString();
    }
}
