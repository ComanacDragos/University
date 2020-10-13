package Model;

import java.text.DecimalFormat;

public class Cylinder implements GeometricObject {
    double radius, height;
    String name;

    public Cylinder(double radius, double height, String name){
        this.radius = radius;
        this.height = height;
        this.name = name;
    }

    @Override
    public double getVolume() {
        return Math.PI * Math.pow(this.radius, 2) * this.height;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public String toString() {
        DecimalFormat df = new DecimalFormat("#.##");
        return "Name: " + this.name + " Radius: " + this.radius + " Height: " + this.height + " Volume: " + df.format(this.getVolume());
    }
}
