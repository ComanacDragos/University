package Model.Expressions;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Values.IValue;

public interface IExpression {
    IValue eval(MyIDictionary<String, IValue> symbolsTable) throws MyException;

    IExpression deepCopy();
}
