import java.io.*;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

public class PolynomialImpl implements Polynomial{
    int[] coefficients;
    int degree;

    public PolynomialImpl(int degree){
        coefficients = new int[degree];
        this.degree = degree;
    }

    public PolynomialImpl(Polynomial polynomial, int start, int end){
        this.coefficients = new int[end-start];
        this.degree = end-start;
        for(int i=start;i<end;i++){
            this.coefficients[i-start] = polynomial.get(i);
        }
    }

    public PolynomialImpl(int degree, String file){
        coefficients = new int[degree];
        this.degree = degree;
        Random rand = new Random();
        for (int i = 0; i < degree-1; i++) {
            coefficients[i] = rand.nextInt(5);
        }
        coefficients[degree-1] = rand.nextInt(5) + 1;
        writeToFile(file);
    }

    public PolynomialImpl(String file){
        try(BufferedReader reader = new BufferedReader(new FileReader(file))){
            List<String> lines = reader.lines().collect(Collectors.toList());
            degree = Integer.parseInt(lines.get(0));
            if(degree != lines.size()-1)
                throw new RuntimeException("Polynomial does not have the given degree");
            coefficients = new int[degree+1];
            for(int i=0;i<degree;i++)
                coefficients[i] = Integer.parseInt(lines.get(i+1));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeToFile(String file){
        try(PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter(file)))){
            writer.println(degree);
            for(int i=0;i<degree;i++)
                writer.println(coefficients[i]);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public int get(int index){
        return coefficients[index];
    }

    public void set(int index, int value){
        coefficients[index] = value;
    }

    public void accumulate(int index, int value){
        coefficients[index] += value;
    }

    @Override
    public int getDegree() {
        return this.degree;
    }

    public void resize(int n){
        int[] newCoefficients = new int[n];
        if (this.degree >= 0)
            System.arraycopy(this.coefficients, 0, newCoefficients, 0, this.degree);
        this.coefficients = newCoefficients;
        this.degree = n;
    }

    public void shift(int n){
        int[] newCoefficients = new int[n+this.degree];
        if (this.degree >= 0)
            System.arraycopy(coefficients, 0, newCoefficients, n, this.degree);
        this.coefficients = newCoefficients;
        this.degree = n+this.degree;
    }

    @Override
    public String toString() {
        StringBuilder representation = new StringBuilder();
        representation.append(coefficients[0]);
        for(int i=1;i<degree;i++)
            representation.append(" + ")
                    .append(coefficients[i])
                    .append("*X^")
                    .append(i);

        return representation.toString();
    }
}
