public class SequentialKaratsubaMultiplier {
    public static Polynomial multiply(Polynomial p, Polynomial q){
        int n = (p.getDegree()+1)/2;
        //Polynomial result = new Polynomial(n+n-1);
        Polynomial p1 = new PolynomialCopy(p, 0, n-1);
        Polynomial p2 = new PolynomialCopy(p, n-1, p.getDegree());

        Polynomial q1 = new PolynomialCopy(q, 0, n-1);
        Polynomial q2 = new PolynomialCopy(q, n-1, p.getDegree());

        Polynomial p1q1 = SequentialRegularMultiplier.multiply(p1, q1);
        PolynomialImpl p2q2 = (PolynomialImpl) SequentialRegularMultiplier.multiply(p2, q2);

        PolynomialImpl middle = (PolynomialImpl) SequentialRegularMultiplier.multiply(
                SequentialAdder.add(p1, p2, 1),
                SequentialAdder.add(q1, q2, 1)
        );
        middle = (PolynomialImpl) SequentialAdder.add(middle, p1q1, -1);
        middle = (PolynomialImpl) SequentialAdder.add(middle, p2q2, -1);
        middle.shift(n);
        p2q2.shift(2*n);
        return SequentialAdder.add(
                p1q1, SequentialAdder.add(middle, p2q2, 1), 1
        );
        /*
        if(p.getDegree() < 5 || q.getDegree() < 5)
            return SequentialRegularMultiplier.multiply(p, q);
        int n = (p.getDegree()+1)/2;
        Polynomial p1 = new PolynomialCopy(p, 0, n);
        Polynomial p2 = new PolynomialCopy(p, n, p.getDegree());

        Polynomial q1 = new PolynomialCopy(q, 0, n);
        Polynomial q2 = new PolynomialCopy(q, n, p.getDegree());
        Polynomial p1q1, p2q2, middle;

        p1q1 = SequentialKaratsubaMultiplier.multiply(p1, q1);

        p2q2 = SequentialKaratsubaMultiplier.multiply(p2, q2);
        middle = SequentialKaratsubaMultiplier.multiply(
                SequentialAdder.add(p1, p2, 1),
                SequentialAdder.add(q1, q2, 1)
        );


        Polynomial result = new PolynomialImpl(p.getDegree() + q.getDegree() - 1);
        for(int i=0;i<p.getDegree()+q.getDegree()-1;i++){
            if(i<p1q1.getDegree())
                result.accumulate(i, p1q1.get(i));
            if(n<=i && i<middle.getDegree()+n) {
                int s = middle.get(i-n);
                if(i-n<p1q1.getDegree())
                    s-= p1q1.get(i-n);
                if(i-n<p2q2.getDegree())
                    s-= p2q2.get(i-n);
                result.accumulate(i, s);
            }
            if(2*n<=i && i<p2q2.getDegree()+2*n)
                result.accumulate(i, p2q2.get(i-2*n));
        }
        return result;
        */
    }
}
