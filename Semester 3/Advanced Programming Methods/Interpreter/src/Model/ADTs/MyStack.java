package Model.ADTs;

import Exceptions.EmptyCollection;
import Exceptions.MyException;

import java.util.Stack;

public class MyStack<T> implements MyIStack<T>{
    Stack<T> stack;

    public MyStack(){
        this.stack = new Stack<>();
    }

    @Override
    public T pop() throws MyException, EmptyCollection {
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
    public String toString() {
        return this.stack.toString();
    }
}
