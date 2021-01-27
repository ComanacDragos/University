package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Types.IType;
import Model.Values.IValue;

public interface IExpression {
    IValue eval(MyIDictionary<String, IValue> symbolsTable, MyHeap heap) throws MyException;

    IType typeCheck(MyIDictionary<String, IType> typeEnvironment) throws  MyException;

    IExpression deepCopy();
}
