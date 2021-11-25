public interface Polynomial {
    int get(int index);
    void set(int index, int value);
    void accumulate(int index, int value);
    int getDegree();
}
