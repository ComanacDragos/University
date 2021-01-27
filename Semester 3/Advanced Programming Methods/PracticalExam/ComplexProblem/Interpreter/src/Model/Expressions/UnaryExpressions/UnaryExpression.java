package Model.Expressions.UnaryExpressions;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Values.IValue;

public abstract class UnaryExpression implements IExpression {
    IExpression expression;

    public UnaryExpression(IExpression expression) {
        this.expression = expression;
    }

    public IExpression getExpression() {
        return expression;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public abstract IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException;

    @Override
    public abstract IExpression deepCopy();
}
