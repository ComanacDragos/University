package Model.Expressions;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class ArithmeticExpression extends BinaryExpression{
   public enum ArithmeticOperation{
       ADDITION,
       SUBTRACTION,
       MULTIPLICATION,
       DIVISION
   }

    ArithmeticOperation operand;

    public ArithmeticExpression(IExpression lhs, IExpression rhs, ArithmeticOperation operand){
        super(lhs, rhs);
        this.operand = operand;
    }

    public ArithmeticOperation getOperand() {
        return operand;
    }

    public void setOperand(ArithmeticOperation operand) {
        this.operand = operand;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable) throws MyException {
        IValue firstValue, secondValue;

        firstValue = this.leftSide.eval(symbolsTable);

        if(firstValue.getType().equals(new IntType())){
            secondValue = this.rightSide.eval(symbolsTable);
            if(secondValue.getType().equals(new IntType())){
                IntValue first = (IntValue)firstValue;
                IntValue second = (IntValue) secondValue;

                switch (this.operand){
                    case ADDITION:
                        return new IntValue(first.getValue() + second.getValue());
                    case SUBTRACTION:
                        return new IntValue(first.getValue() - second.getValue());
                    case MULTIPLICATION:
                        return new IntValue(first.getValue() * second.getValue());
                    case DIVISION:
                        if(second.getValue() == 0)
                            throw new DivisionByZero();
                        else
                            return new IntValue(first.getValue() / second.getValue());
                    default:
                        throw new MyException("Invalid operation");
                }
            }
            else
                throw new MyException("Second operand is not an integer");
        }
        else
            throw new MyException("First operand is not an integer");
    }

    @Override
    public ArithmeticExpression deepCopy() {
        return new ArithmeticExpression(this.leftSide.deepCopy(), this.rightSide.deepCopy(), this.operand);
    }

    @Override
    public String toString() {
        char operandSymbol = switch (this.operand){
            case ADDITION -> '+';
            case DIVISION -> '/';
            case SUBTRACTION -> '-';
            case MULTIPLICATION -> '*';
        };

        return "(" + this.leftSide.toString() + ' ' + operandSymbol + ' ' + this.rightSide.toString() + ')';
    }
}
