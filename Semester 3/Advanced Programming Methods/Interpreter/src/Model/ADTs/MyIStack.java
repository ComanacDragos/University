package Model.ADTs;

public interface MyIStack<T> {
    T pop();
    void push(T element);
    T top();
    Boolean isEmpty();
}
