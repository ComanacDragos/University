public class SequentialAdder {
    public static Polynomial add(Polynomial p, Polynomial q, int multiplier){
        Polynomial small, big;
        if(p.degree < q.degree){
            small = p;
            big = q;
        }else{
            small = q;
            big = p;
        }
        Polynomial result = new Polynomial(big, 0, big.degree);
        for(int i=0;i<small.degree;i++)
            result.accumulate(i, multiplier*small.get(i));
        return result;
    }
}
