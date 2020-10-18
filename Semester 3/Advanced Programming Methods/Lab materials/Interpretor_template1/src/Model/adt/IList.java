package Model.adt;

public interface IList<T> {
    void add(T v);
    T pop();
    String toString();
}
