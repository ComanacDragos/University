package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;

public class VariableDeclarationStatement implements IStatement{
    String variable_name;
    IType type;

    public VariableDeclarationStatement(String variable_name, IType type){
        this.variable_name = variable_name;
        this.type = type;
    }

    public IType getType() {
        return type;
    }

    public String getVariable_name() {
        return variable_name;
    }

    public void setVariable_name(String variable_name) {
        this.variable_name = variable_name;
    }

    public void setType(IType type) {
        this.type = type;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        if(symbolsTable.isDefined(this.variable_name))
            throw new MyException("Variable is already declared");
        else
            if(this.type instanceof IntType)
                symbolsTable.put(this.variable_name, new IntValue());
            else if(this.type instanceof BoolType)
                symbolsTable.put(this.variable_name, new BoolValue());
            else if(this.type instanceof StringType)
                symbolsTable.put(this.variable_name, new StringValue());
            else
                throw new MyException("Type not defined");
        return state;
    }

    @Override
    public VariableDeclarationStatement deepCopy() {
        return new VariableDeclarationStatement(this.variable_name, this.type);
    }

    @Override
    public String toString() {
        return this.type.toString() + " = " + this.variable_name + ';';
    }
}
