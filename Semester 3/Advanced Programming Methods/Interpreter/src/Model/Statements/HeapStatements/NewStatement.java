package Model.Statements.HeapStatements;

import Exceptions.MyException;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.ReferenceType;
import Model.Values.IValue;
import Model.Values.ReferenceValue;

public class NewStatement implements IStatement {
    String variableName;
    IExpression expression;

    public NewStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();
        MyHeap heap = state.getHeap();

        if(symbolsTable.isDefined(this.variableName)){
            IValue variableValue = symbolsTable.lookup(this.variableName);

            if(variableValue.getType() instanceof ReferenceType){
                ReferenceValue referenceValue = (ReferenceValue) variableValue;

                IValue value = this.expression.eval(symbolsTable, heap);

                if(referenceValue.getLocationType().equals(value.getType())){
                    Integer address = heap.put(value);
                    symbolsTable.put(this.variableName, new ReferenceValue(address, referenceValue.getLocationType()));
                }
                else{
                    throw new MyException(this.variableName + " is not a reference to " + value.getType().toString());
                }
            }
            else {
                throw new MyException(this.variableName + " is not a reference type");
            }
        }
        else{
            throw new MyException(this.variableName + " is not defined");
        }

        return null;
    }

    @Override
    public NewStatement deepCopy() {
        return new NewStatement(this.variableName, this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "new(" + this.variableName + ", " + this.expression.toString() + ");";
    }
}
