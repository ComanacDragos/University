public class Addition extends ComplexExpression {
    Addition(Operation operation, NumarComplex[] args)
    {
        super(operation, args);
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
