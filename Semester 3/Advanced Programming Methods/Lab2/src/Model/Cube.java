package Model;

import java.text.DecimalFormat;

public class Cube implements GeometricObject {
    double sideLength;
    String name;

    public Cube(double sideLength, String name) {
        this.sideLength = sideLength;
        this.name = name;
    }

    @Override
    public double getVolume() {
        return Math.pow(this.sideLength, 3);
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public String toString() {
        DecimalFormat df = new DecimalFormat("#.##");
        return "Name: " + this.name + " Radius: " + sideLength + " Volume: " + df.format(this.getVolume());
    }
}
