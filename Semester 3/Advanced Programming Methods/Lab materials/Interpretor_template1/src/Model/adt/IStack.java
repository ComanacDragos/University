package Model.adt;

public interface IStack<T> {

    T pop();
    void push(T v);
    boolean isEmpty();
    String toString();
}

