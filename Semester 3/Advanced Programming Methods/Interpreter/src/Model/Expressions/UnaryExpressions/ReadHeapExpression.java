package Model.Expressions.UnaryExpressions;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Types.ReferenceType;
import Model.Values.IValue;
import Model.Values.ReferenceValue;

public class ReadHeapExpression extends UnaryExpression {
    public ReadHeapExpression(IExpression expression) {
        super(expression);
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException {
        IValue value = this.expression.eval(symbolsTable, heap);

        if(value.getType() instanceof ReferenceType){
            ReferenceValue referenceValue = (ReferenceValue) value;

            if(heap.isDefined(referenceValue.getAddress())){
                return heap.lookup(referenceValue.getAddress());
            }
            else{
                throw new MyException("Value does not exist in the heap");
            }
        }
        else{
            throw new MyException("Expression must be a reference value");
        }
    }

    @Override
    public IExpression deepCopy() {
        return new ReadHeapExpression(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "readHeap(" + this.expression.toString() + ")";
    }
}
