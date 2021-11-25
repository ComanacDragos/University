public class PolynomialCopy implements Polynomial{
    Polynomial polynomial;
    Integer start, end, degree;

    public PolynomialCopy(Polynomial polynomial, Integer start, Integer end){
        this.degree = end-start;
        this.start = start;
        this.end = end;
        this.polynomial = polynomial;
    }

    public int get(int index){
        return this.polynomial.get(index+start);
    }

    @Override
    public void set(int index, int value) {
        polynomial.set(index+start, value);
    }

    @Override
    public void accumulate(int index, int value) {
        polynomial.accumulate(index+start, value);
    }

    @Override
    public int getDegree() {
        return this.degree;
    }

    @Override
    public String toString() {
        StringBuilder representation = new StringBuilder();
        representation.append(get(0));
        for(int i=1;i<degree;i++)
            representation.append(" + ")
                    .append(get(i))
                    .append("*X^")
                    .append(i);

        return representation.toString();
    }
}
