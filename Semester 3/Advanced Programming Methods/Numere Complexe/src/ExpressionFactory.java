public class ExpressionFactory {
    public ComplexExpression createExpression(ComplexExpression.Operation operation, NumarComplex[] args)
    {
        if(operation == ComplexExpression.Operation.ADDITION)
            return new Addition(operation, args);
        return new Substraction(operation, args);

    }

}
