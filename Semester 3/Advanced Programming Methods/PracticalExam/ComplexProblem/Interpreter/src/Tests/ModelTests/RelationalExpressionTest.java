package Tests.ModelTests;

import Exceptions.MyException;
import Model.ADTs.MyDictionary;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Expressions.BinaryExpressions.RelationalExpression;
import Model.Expressions.ValueExpression;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class RelationalExpressionTest {
    IExpression left, right, invalid;
    RelationalExpression expression;
    MyIDictionary<String, IValue> symbolsTable;
    MyHeap heap;

    @BeforeEach
    void setUp() {
        this.left = new ValueExpression(new IntValue(5));
        this.right = new ValueExpression(new IntValue(10));
        this.invalid = new ValueExpression(new StringValue("invalid"));

        this.heap = new MyHeap();
        this.symbolsTable = new MyDictionary<>();
    }

    void ExpressionShouldBeTrue(){
        IValue value = this.expression.eval(this.symbolsTable, this.heap);

        Assertions.assertTrue(value instanceof BoolValue);
        Assertions.assertTrue(((BoolValue) value).getValue());
    }

    void ExpressionShouldBeFalse(){
        IValue value = this.expression.eval(this.symbolsTable, this.heap);

        Assertions.assertTrue(value instanceof BoolValue);
        Assertions.assertFalse(((BoolValue) value).getValue());
    }

    @Test
    void LessThanExpressionShouldReturnTrue() {
        this.expression = new RelationalExpression(this.left, this.right, RelationalExpression.RelationalOperation.LESS_THAN);
        this.ExpressionShouldBeTrue();
    }

    @Test
    void LessThanExpressionShouldReturnFalse() {
        this.expression = new RelationalExpression(this.right, this.left, RelationalExpression.RelationalOperation.LESS_THAN);
        this.ExpressionShouldBeFalse();
    }

    @Test
    void LessThanOrEqualExpressionShouldReturnTrue() {
        this.expression = new RelationalExpression(this.left, this.right, RelationalExpression.RelationalOperation.LESS_THAN_OR_EQUAL);
        this.ExpressionShouldBeTrue();
    }

    @Test
    void LessThanOrEqualExpressionShouldReturnFalse() {
        this.expression = new RelationalExpression(this.right, this.left, RelationalExpression.RelationalOperation.LESS_THAN_OR_EQUAL);
        this.ExpressionShouldBeFalse();
    }

    @Test
    void EqualExpressionShouldReturnTrue() {
        this.expression = new RelationalExpression(this.left, this.left, RelationalExpression.RelationalOperation.EQUAL);
        this.ExpressionShouldBeTrue();
    }

    @Test
    void EqualExpressionShouldReturnFalse() {
        this.expression = new RelationalExpression(this.right, this.left, RelationalExpression.RelationalOperation.EQUAL);
        this.ExpressionShouldBeFalse();
    }

    @Test
    void NotEqualExpressionShouldReturnTrue() {
        this.expression = new RelationalExpression(this.left, this.right, RelationalExpression.RelationalOperation.NOT_EQUAL);
        this.ExpressionShouldBeTrue();
    }

    @Test
    void NotEqualExpressionShouldReturnFalse() {
        this.expression = new RelationalExpression(this.left, this.left, RelationalExpression.RelationalOperation.NOT_EQUAL);
        this.ExpressionShouldBeFalse();
    }

    @Test
    void GreaterThanExpressionShouldReturnTrue() {
        this.expression = new RelationalExpression(this.right, this.left, RelationalExpression.RelationalOperation.GREATER_THAN);
        this.ExpressionShouldBeTrue();
    }

    @Test
    void GreaterThanExpressionShouldReturnFalse() {
        this.expression = new RelationalExpression(this.left, this.right, RelationalExpression.RelationalOperation.GREATER_THAN);
        this.ExpressionShouldBeFalse();
    }

    @Test
    void GreaterThanOrEqualExpressionShouldReturnTrue() {
        this.expression = new RelationalExpression(this.right, this.left, RelationalExpression.RelationalOperation.GREATER_THAN_OR_EQUAL);
        this.ExpressionShouldBeTrue();
    }

    @Test
    void GreaterThanOrEqualExpressionShouldReturnFalse() {
        this.expression = new RelationalExpression(this.left, this.right, RelationalExpression.RelationalOperation.GREATER_THAN_OR_EQUAL);
        this.ExpressionShouldBeFalse();
    }

    @Test
    void EvalShouldThrowMyExceptionWithMessageFirstOperandIsNotAnInteger(){
        this.expression = new RelationalExpression(this.invalid, this.right, RelationalExpression.RelationalOperation.LESS_THAN);

        Exception exception = Assertions.assertThrows(MyException.class, ()->{this.expression.eval(this.symbolsTable, this.heap);});

        Assertions.assertEquals(exception.getMessage(), "First operand is not an integer");
    }

    @Test
    void EvalShouldThrowMyExceptionWithMessageSecondOperandIsNotAnInteger(){
        this.expression = new RelationalExpression(this.left, this.invalid, RelationalExpression.RelationalOperation.LESS_THAN);

        Exception exception = Assertions.assertThrows(MyException.class, ()->{this.expression.eval(this.symbolsTable, this.heap);});

        Assertions.assertEquals(exception.getMessage(), "Second operand is not an integer");
    }

}
