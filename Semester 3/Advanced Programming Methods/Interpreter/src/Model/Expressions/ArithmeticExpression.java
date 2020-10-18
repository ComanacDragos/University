package Model.Expressions;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class ArithmeticExpression implements IExpression{
    IExpression expression1;
    IExpression expression2;
    char operand;

    public ArithmeticExpression(IExpression expression1, IExpression expression2, char operand){
        this.expression1 = expression1;
        this.expression2 = expression2;
        this.operand = operand;
    }

    public char getOperand() {
        return operand;
    }

    public IExpression getExpression1() {
        return expression1;
    }

    public IExpression getExpression2() {
        return expression2;
    }

    public void setExpression1(IExpression expression1) {
        this.expression1 = expression1;
    }

    public void setExpression2(IExpression expression2) {
        this.expression2 = expression2;
    }

    public void setOperand(char operand) {
        this.operand = operand;
    }

    public IntType getType(){
        return new IntType();
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable) throws MyException, DivisionByZero {
        IValue value1, value2;

        value1 = this.expression1.eval(symbolsTable);

        if(value1.getType().equals(new IntType())){
            value2 = this.expression2.eval(symbolsTable);
            if(value2.getType().equals(new IntType())){
                IntValue first = (IntValue)value1;
                IntValue second = (IntValue) value2;

                switch (this.operand){
                    case '+':
                        return new IntValue(first.getValue() + second.getValue());
                    case '-':
                        return new IntValue(first.getValue() - second.getValue());
                    case '*':
                        return new IntValue(first.getValue() * second.getValue());
                    case '/':
                        if(second.getValue() == 0)
                            throw new DivisionByZero();
                        else
                            return new IntValue(first.getValue() / second.getValue());
                    default:
                        throw new MyException("Bad operand");
                }
            }
            else
                throw new MyException("Second operand is not an integer");
        }
        else
            throw new MyException("First operand is not an integer");
    }

    @Override
    public String toString() {
        return "(" + expression1.toString() + ' ' + this.operand + ' ' + this.expression2.toString() + ')';
    }
}
