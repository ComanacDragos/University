package Model.Statements.HeapStatements;

import Exceptions.MyException;
import Exceptions.VariableNotDefined;
import Model.ADTs.MyHeap;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.IType;
import Model.Types.ReferenceType;
import Model.Values.IValue;
import Model.Values.ReferenceValue;

public class WriteHeapStatement implements IStatement {
    String variableName;
    IExpression expression;

    public WriteHeapStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    public String getVariableName() {
        return variableName;
    }

    public void setVariableName(String variableName) {
        this.variableName = variableName;
    }

    public IExpression getExpression() {
        return expression;
    }

    public void setExpression(IExpression expression) {
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

                if(heap.isDefined(referenceValue.getAddress())){
                    IValue expressionValue = this.expression.eval(symbolsTable, heap);

                    if(expressionValue.getType().equals(referenceValue.getLocationType())){
                        heap.put(referenceValue.getAddress(), expressionValue);
                    }
                    else{
                        throw new MyException(this.variableName + " is not a reference to " + expressionValue.getType());
                    }
                }
                else{
                    throw new MyException(referenceValue.getAddress() + " is not defined in heap");
                }
            }
            else{
                throw new MyException("Variable is not a reference value");
            }
        }
        else{
            throw new MyException(this.variableName + " is not defined");
        }

        return null;
    }

    @Override
    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnvironment) throws MyException {
        IType variableType;

        try {
            variableType = typeEnvironment.lookup(this.variableName);
        }
        catch (MyException exception){
            throw new VariableNotDefined(this.variableName);
        }

        IType expressionType = this.expression.typeCheck(typeEnvironment);

        if(variableType.equals(new ReferenceType(expressionType))){
            return typeEnvironment;
        }
        else{
            throw new MyException("Write heap statement: variable is not a reference to expression type");
        }
    }

    @Override
    public IStatement deepCopy() {
        return new WriteHeapStatement(this.variableName, this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "writeHeap(" + this.variableName + ", " + this.expression.toString() + ");";
    }
}
