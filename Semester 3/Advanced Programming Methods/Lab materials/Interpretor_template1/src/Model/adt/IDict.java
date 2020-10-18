package Model.adt;

public interface IDict<T1,T2>{

    void add(T1 v1, T2 v2);
    void update(T1 v1, T2 v2);
    T2 lookup(T1 id);
    boolean isDefined(String id);
    String toString();
}
