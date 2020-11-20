package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ProgramState;
import Model.Types.*;
import Model.Values.*;

public class VariableDeclarationStatement implements IStatement{
    String variableName;
    IType type;

    public VariableDeclarationStatement(String variableName, IType type){
        this.variableName = variableName;
        this.type = type;
    }

    public IType getType() {
        return type;
    }

    public String getVariableName() {
        return variableName;
    }

    public void setVariableName(String variableName) {
        this.variableName = variableName;
    }

    public void setType(IType type) {
        this.type = type;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        if(symbolsTable.isDefined(this.variableName))
            throw new MyException("Variable is already declared");
        else
            if(this.type instanceof IntType)
                symbolsTable.put(this.variableName, new IntValue());
            else if(this.type instanceof BoolType)
                symbolsTable.put(this.variableName, new BoolValue());
            else if(this.type instanceof StringType)
                symbolsTable.put(this.variableName, new StringValue());
            else if(this.type instanceof ReferenceType)
                symbolsTable.put(this.variableName, new ReferenceValue(((ReferenceType) this.type).getInnerType()));
            else
                throw new MyException("Type not defined");
        return null;
    }

    @Override
    public VariableDeclarationStatement deepCopy() {
        return new VariableDeclarationStatement(this.variableName, this.type);
    }

    @Override
    public String toString() {
        return this.type.toString() + ' ' + this.variableName + ';';
    }
}
