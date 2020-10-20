package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;

public class VariableDeclarationStatement implements IStatement{
    String name;
    IType type;

    public VariableDeclarationStatement(String name, IType type){
        this.name = name;
        this.type = type;
    }

    public IType getType() {
        return type;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setType(IType type) {
        this.type = type;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        if(symbolsTable.isDefined(this.name))
            throw new MyException("Variable is already declared");
        else
            if(this.type instanceof IntType)
                symbolsTable.put(this.name, new IntValue());
            else if(this.type instanceof BoolType)
                symbolsTable.put(this.name, new BoolValue());
        return state;
    }

    @Override
    public String toString() {
        return this.type.toString() + " = " + this.name;
    }
}
