package Model.Expressions;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class ArithmeticExpression implements IExpression{
    IExpression lhs;
    IExpression rhs;
    char operand;

    public ArithmeticExpression(IExpression lhs, IExpression rhs, char operand){
        this.lhs = lhs;
        this.rhs = rhs;
        this.operand = operand;
    }

    public char getOperand() {
        return operand;
    }

    public IExpression getLhs() {
        return lhs;
    }

    public IExpression getRhs() {
        return rhs;
    }

    public void setExpression1(IExpression expression1) {
        this.lhs = expression1;
    }

    public void setExpression2(IExpression expression2) {
        this.rhs = expression2;
    }

    public void setOperand(char operand) {
        this.operand = operand;
    }

    public IntType getType(){
        return new IntType();
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable) throws MyException, DivisionByZero {
        IValue firstValue, secondValue;

        firstValue = this.lhs.eval(symbolsTable);

        if(firstValue.getType().equals(new IntType())){
            secondValue = this.rhs.eval(symbolsTable);
            if(secondValue.getType().equals(new IntType())){
                IntValue first = (IntValue)firstValue;
                IntValue second = (IntValue) secondValue;

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
        return "(" + lhs.toString() + ' ' + this.operand + ' ' + this.rhs.toString() + ')';
    }
}
