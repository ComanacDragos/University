public class SequentialRegularMultiplier {
     public static Polynomial multiply(Polynomial p, Polynomial q){
        int n = p.getDegree();
        int m = q.getDegree();
         Polynomial result = new PolynomialImpl(n+m-1);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                result.accumulate(i+j, p.get(i)*q.get(j));
        return result;
    }
}
