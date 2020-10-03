public abstract class ComplexExpression {
    public enum Operation
    {
        ADDITION,
        SUBSTRACTION,
        MULTIPLICATION,
        DIVISION
    }
    Operation operation;
    NumarComplex[] args;
    ComplexExpression(Operation operation, NumarComplex[] args)
    {
        this.operation = operation;
        this.args = args;
    }

    public NumarComplex execute()
    {
        return this.executeOneOperation();
    }

    public abstract NumarComplex executeOneOperation();
}
