package Repository;

import Exceptions.BadDimension;
import Exceptions.MyException;
import Exceptions.RepositoryException;
import Model.GeometricObject;

public interface Repository {
    void store(GeometricObject object) throws RepositoryException, MyException;

    GeometricObject get(int index) throws BadDimension;

    int getSize();

    GeometricObject[] getAll();
}
