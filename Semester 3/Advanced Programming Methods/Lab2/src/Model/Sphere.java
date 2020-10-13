package Model;

import java.text.DecimalFormat;

public class Sphere implements GeometricObject {
    double radius;
    String name;

    public Sphere(double radius, String name){
        this.radius = radius;
        this.name = name;
    }

    @Override
    public double getVolume() {
        return (4.0/3) * Math.PI * Math.pow(this.radius, 3);
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public String toString() {
        DecimalFormat df = new DecimalFormat("#.##");
        return "Name: " + this.name + " Radius: " + this.radius + " Volume: " + df.format(this.getVolume());
    }
}
