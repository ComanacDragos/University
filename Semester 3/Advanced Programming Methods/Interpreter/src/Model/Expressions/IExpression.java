package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Values.IValue;

public interface IExpression {
    IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException;

    IExpression deepCopy();
}
