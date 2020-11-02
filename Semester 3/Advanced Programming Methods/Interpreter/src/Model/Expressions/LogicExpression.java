package Model.Expressions;

import Exceptions.DivisionByZero;
import Exceptions.FullCollection;
import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
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
    public IValue eval(MyIDictionary<String, IValue> symbolsTable) throws DivisionByZero {
        IValue firstValue, secondValue;
        firstValue = this.leftSide.eval(symbolsTable);
        if(firstValue.getType().equals(new BoolType())){
            secondValue = this.rightSide.eval(symbolsTable);
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
    public String toString() {
        return '(' + this.leftSide.toString() + ' ' + this.operand + ' ' + this.rightSide.toString() + ')';
    }
}
