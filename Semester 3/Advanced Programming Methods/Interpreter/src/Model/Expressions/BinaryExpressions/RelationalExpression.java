package Model.Expressions.BinaryExpressions;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;

public class RelationalExpression extends BinaryExpression{
    public enum RelationalOperation{
        LESS_THAN,
        LESS_THAN_OR_EQUAL,
        EQUAL,
        NOT_EQUAL,
        GREATER_THAN,
        GREATER_THAN_OR_EQUAL
    }

    RelationalOperation operand;

    public RelationalExpression(IExpression leftSide, IExpression rightSide, RelationalOperation operand) {
        super(leftSide, rightSide);
        this.operand = operand;
    }

    public RelationalOperation getOperand() {
        return operand;
    }

    public void setOperand(RelationalOperation operand) {
        this.operand = operand;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException {
        IValue firstValue, secondValue;

        firstValue = this.leftSide.eval(symbolsTable, heap);

        if(firstValue.getType().equals(new IntType())){
            secondValue = this.rightSide.eval(symbolsTable, heap);
            if(secondValue.getType().equals(new IntType())){
                IntValue first = (IntValue)firstValue;
                IntValue second = (IntValue) secondValue;

                return switch (this.operand) {
                    case LESS_THAN -> new BoolValue(first.getValue() < second.getValue());
                    case LESS_THAN_OR_EQUAL -> new BoolValue(first.getValue() <= second.getValue());
                    case EQUAL -> new BoolValue(first.equals(second));
                    case NOT_EQUAL -> new BoolValue(!first.equals(second));
                    case GREATER_THAN -> new BoolValue(first.getValue() > second.getValue());
                    case GREATER_THAN_OR_EQUAL -> new BoolValue(first.getValue() >= second.getValue());
                };
            }
            else
                throw new MyException("Second operand is not an integer");
        }
        else
            throw new MyException("First operand is not an integer");
    }

    @Override
    public RelationalExpression deepCopy() {
        return new RelationalExpression(this.leftSide, this.rightSide, this.operand);
    }

    @Override
    public String toString() {
        String operandAsString = switch (this.operand){
            case LESS_THAN -> "<";
            case LESS_THAN_OR_EQUAL -> "<=";
            case EQUAL -> "==";
            case NOT_EQUAL -> "!=";
            case GREATER_THAN -> ">";
            case GREATER_THAN_OR_EQUAL -> ">=";
        };
        return this.leftSide.toString() + ' ' + operandAsString + ' ' + this.rightSide.toString();
    }
}
