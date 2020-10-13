package Repository;

import Exceptions.BadDimension;
import Exceptions.MyException;
import Exceptions.RepositoryException;
import Model.GeometricObject;

public class InMemoryRepository implements Repository{
    GeometricObject[] items;
    int size;

    public InMemoryRepository(int repositorySize){
        this.items = new GeometricObject[repositorySize];
        this.size = 0;
    }

    @Override
    public void store(GeometricObject object) throws MyException, RepositoryException {
        for(int i=0;i<this.size;i+=1)
            if(object.getName().compareTo(this.items[i].getName()) == 0)
                throw new RepositoryException("Object already exists");

        if(size == this.items.length)
            throw new MyException("Repository is full");

        this.items[this.size] = object;
        this.size += 1;
    }

    @Override
    public GeometricObject get(int index) throws BadDimension {
        if(index < 0 || index >= this.size)
            throw new BadDimension("Index out of range");
        return this.items[index];
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public GeometricObject[] getAll() {
        GeometricObject[] newObjects = new GeometricObject[this.size];
        System.arraycopy(this.items, 0, newObjects, 0, this.size);
        return newObjects;
    }
}
