public class Subtraction extends ComplexExpression{
    Subtraction(NumarComplex[] args)
    {
        super(Operation.SUBTRACTION, args);
    }

    @Override
    public NumarComplex executeOneOperation()
    {
        NumarComplex rez = this.args[0];

        for(int i=1;i<args.length;i+=1)
            rez = rez.scadere(args[i]);

        return rez;
    }
}
