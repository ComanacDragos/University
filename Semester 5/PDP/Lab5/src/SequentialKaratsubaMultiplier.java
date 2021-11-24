public class SequentialKaratsubaMultiplier {
    public static Polynomial multiply(Polynomial p, Polynomial q){
        int n = (p.degree+1)/2;
        //Polynomial result = new Polynomial(n+n-1);
        Polynomial p1 = new Polynomial(p, 0, n);
        Polynomial p2 = new Polynomial(p, n, p.degree);

        Polynomial q1 = new Polynomial(q, 0, n);
        Polynomial q2 = new Polynomial(q, n, p.degree);

        Polynomial p1q1 = SequentialRegularMultiplier.multiply(p1, q1);
        Polynomial p2q2 = SequentialRegularMultiplier.multiply(p2, q2);

        Polynomial middle = SequentialRegularMultiplier.multiply(
                SequentialAdder.add(p1, p2, 1),
                SequentialAdder.add(q1, q2, 1)
        );
        middle = SequentialAdder.add(middle, p1q1, -1);
        middle = SequentialAdder.add(middle, p2q2, -1);
        /*middle.shift(n);
        p2q2.shift(2*n);
        return SequentialAdder.add(
                p1q1, SequentialAdder.add(middle, p2q2, 1), 1
        );*/
        Polynomial result = new Polynomial(p.degree + q.degree - 1);
        for(int i=0;i<p.degree+q.degree-1;i++){
            if(i<p1q1.degree)
                result.accumulate(i, p1q1.get(i));
            if(n<=i && i<middle.degree+n)
                result.accumulate(i, middle.get(i-n));
            if(2*n<=i && i<p2q2.degree+2*n)
                result.accumulate(i, p2q2.get(i-2*n));
        }

        return result;
    }
}
