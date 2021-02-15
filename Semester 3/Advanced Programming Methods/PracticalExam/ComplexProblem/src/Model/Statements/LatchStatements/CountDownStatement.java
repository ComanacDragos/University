package Model.Statements.LatchStatements;

import Exceptions.MyException;
import Exceptions.VariableNotDefined;
import Model.ADTs.MyIDictionary;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class CountDownStatement implements IStatement {
    String variableName;

    public CountDownStatement(String variableName) {
        this.variableName = variableName;
    }

    public String getVariableName() {
        return variableName;
    }

    public void setVariableName(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        if(state.getSymbolsTable().isDefined(this.variableName)){
            IValue value = state.getSymbolsTable().lookup(this.variableName);
            if(value.getType().equals(new IntType())){
                IntValue foundIndex = (IntValue)value;
                synchronized (state.getLatchTable()){
                    if(state.getLatchTable().isDefined(foundIndex.getValue())) {
                        state.getLatchTable().countDown(foundIndex.getValue());
                        state.getOut().add(new IntValue(state.getProgramId()));
                    }
                }
            }else{
                throw new MyException(this.variableName + " must be an int");
            }
        }else{
            throw new VariableNotDefined(this.variableName);
        }
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnvironment) throws MyException {
        if(typeEnvironment.isDefined(this.variableName)){
            if(!typeEnvironment.lookup(this.variableName).equals(new IntType()))
                throw new MyException(this.variableName + " must be an integer");
        }else{
            throw new VariableNotDefined(this.variableName);
        }
        return typeEnvironment;
    }

    @Override
    public IStatement deepCopy() {
        return new CountDownStatement(this.variableName);
    }

    @Override
    public String toString() {
        return "countDown(" + this.variableName + ");";
    }
}
