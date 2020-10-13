package Controller;

import Exceptions.*;
import Model.Cube;
import Model.Cylinder;
import Model.GeometricObject;
import Model.Sphere;
import Repository.Repository;

public class Controller {
    Repository repository;

    public Controller(Repository repository){
        this.repository = repository;
    }

    public void storeCube(double sideLength, String name) throws MyException {
        if(sideLength <= 0)
            throw new BadDimension("Bad side length");

        if(name.isEmpty())
            throw new BadName("Empty name");

        this.repository.store(new Cube(sideLength, name));
    }

    public void storeSphere(double radius, String name) throws MyException {
        if(radius <= 0)
            throw new BadDimension("Bad radius");

        if(name.isEmpty())
            throw  new BadName("Empty name");

        this.repository.store(new Sphere(radius, name));
    }

    public void storeCylinder(double radius, double height, String name) throws MyException {
        if(radius <= 0)
            throw new BadDimension("Bad radius");

        if(height <= 0)
            throw new BadDimension("Bad height");

        if(name.isEmpty())
            throw  new BadName("Empty name");

        this.repository.store(new Cylinder(radius, height, name));
    }

    public GeometricObject[] getObjects(double minimumVolume) throws BadDimension {
        if(minimumVolume <= 0)
            throw new BadDimension("Bad minimum volume");

        GeometricObject[] objects = new GeometricObject[100];
        int size = 0;

        for(int i=0;i<this.repository.getSize();i+=1){
            GeometricObject current = this.repository.get(i);
            if(current.getVolume() >= minimumVolume) {
                objects[size] = current;
                size += 1;
            }
        }

        GeometricObject[] newObjects = new GeometricObject[size];

        System.arraycopy(objects, 0, newObjects, 0, size);

        return newObjects;
    }

    public GeometricObject[] getAll(){
        return this.repository.getAll();
    }
}

