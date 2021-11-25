public class SequentialAdder {
    public static Polynomial add(Polynomial p, Polynomial q, int multiplier){
        Polynomial small, big;
        if(p.getDegree() < q.getDegree()){
            small = p;
            big = q;
        }else{
            small = q;
            big = p;
        }
        Polynomial result = new PolynomialImpl(big.getDegree());
        for(int i=0;i<result.getDegree();i++) {
            result.set(i, big.get(i));
            if(i<small.getDegree())
                result.accumulate(i, multiplier * small.get(i));
        }
        return result;
    }
}
