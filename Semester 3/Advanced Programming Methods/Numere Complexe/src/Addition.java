public class Addition extends ComplexExpression {
    Addition(NumarComplex[] args)
    {
        super(Operation.ADDITION, args);
    }

    @Override
    public NumarComplex executeOneOperation()
    {
        NumarComplex rez = this.args[0];

        for(int i=1;i<args.length;i+=1)
            rez = rez.adunare(args[i]);

        return rez;
    }
}
