package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class LogicExpression implements IExpression{
    public enum LogicOperand{
        AND,
        OR
    }

    IExpression expression1;
    IExpression expression2;
    LogicOperand operand;

    public LogicExpression(IExpression expression1, IExpression expression2, LogicOperand operand) {
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operand = operand;
    }

    public IExpression getExpression2() {
        return expression2;
    }

    public IExpression getExpression1() {
        return expression1;
    }

    public LogicOperand getOperand() {
        return operand;
    }

    public void setOperand(LogicOperand operand) {
        this.operand = operand;
    }

    public void setExpression2(IExpression expression2) {
        this.expression2 = expression2;
    }

    public void setExpression1(IExpression expression1) {
        this.expression1 = expression1;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable) throws MyException {
        IValue value1, value2;

        value1 = this.expression1.eval(symbolsTable);
        if(value1.getType().equals(new BoolType())){
            value2 = this.expression2.eval(symbolsTable);
            if(value2.getType().equals(new BoolType())){
                BoolValue first = (BoolValue)value1;
                BoolValue second = (BoolValue)value2;

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
        return '(' + this.expression1.toString() + ' ' + this.operand + ' ' + this.expression2.toString() + ')';
    }
}
