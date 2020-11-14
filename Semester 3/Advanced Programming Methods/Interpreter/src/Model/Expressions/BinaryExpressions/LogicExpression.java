package Model.Expressions.BinaryExpressions;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class LogicExpression extends BinaryExpression{
    public enum LogicOperand{
        AND,
        OR
    }

    LogicOperand operand;

    public LogicExpression(IExpression lhs, IExpression rhs, LogicOperand operand) {
        super(lhs, rhs);
        this.operand = operand;
    }

    public LogicOperand getOperand() {
        return operand;
    }

    public void setOperand(LogicOperand operand) {
        this.operand = operand;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException {
        IValue firstValue, secondValue;
        firstValue = this.leftSide.eval(symbolsTable, heap);
        if(firstValue.getType().equals(new BoolType())){
            secondValue = this.rightSide.eval(symbolsTable, heap);
            if(secondValue.getType().equals(new BoolType())){
                BoolValue first = (BoolValue)firstValue;
                BoolValue second = (BoolValue)secondValue;

                return switch (this.operand) {
                    case OR -> new BoolValue(first.getValue() || second.getValue());
                    case AND -> new BoolValue(first.getValue() && second.getValue());
                };
            }
            else
                throw new MyException("Second operand is not boolean");
        }
        else
            throw new MyException("First operand is not boolean");
    }

    @Override
    public LogicExpression deepCopy() {
        return new LogicExpression(this.leftSide.deepCopy(), this.rightSide.deepCopy(), this.operand);
    }

    @Override
    public String toString() {
        return '(' + this.leftSide.toString() + ' ' + this.operand + ' ' + this.rightSide.toString() + ')';
    }
}
