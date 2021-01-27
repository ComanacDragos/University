package Model.Expressions.BinaryExpressions;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Values.IValue;

public abstract class BinaryExpression implements IExpression {
    IExpression leftSide;
    IExpression rightSide;
    public BinaryExpression(IExpression leftSide, IExpression rightSide){
        this.leftSide = leftSide;
        this.rightSide = rightSide;
    }

    public IExpression getLeftSide() {
        return leftSide;
    }

    public IExpression getRightSide() {
        return rightSide;
    }

    public void setLeftSide(IExpression leftSide) {
        this.leftSide = leftSide;
    }

    public void setRightSide(IExpression rightSide) {
        this.rightSide = rightSide;
    }

    @Override
    public abstract IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException, DivisionByZero;
}
