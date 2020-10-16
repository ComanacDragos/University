package Repository;
import Model.IVegetable;

public interface IRepo {

    void add(IVegetable elem) throws MyException;
    void remove(int pos) throws MyException;
    IVegetable[] getAll();
    IVegetable[] filter();
    String toString();
}
