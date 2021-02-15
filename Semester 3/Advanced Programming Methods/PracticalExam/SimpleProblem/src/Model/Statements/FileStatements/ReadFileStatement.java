package Model.Statements.FileStatements;

import Exceptions.MyException;
import Exceptions.VariableNotDefined;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    IExpression expression;
    String variableName;

    public ReadFileStatement(IExpression expression, String variableName) {
        this.expression = expression;
        this.variableName = variableName;
    }

    public IExpression getExpression() {
        return expression;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    public String getVariableName() {
        return variableName;
    }

    public void setVariableName(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();

        if(symbolsTable.isDefined(this.variableName)) {
            IValue variableValue = symbolsTable.lookup(this.variableName);

            if(variableValue.getType().equals(new IntType())){
                IValue stringValue = this.expression.eval(symbolsTable, state.getHeap());

                if(stringValue.getType().equals(new StringType())){
                    StringValue fileName = (StringValue) stringValue;

                    if(fileTable.isDefined(fileName.getValue())){
                        BufferedReader reader = fileTable.lookup(fileName.getValue());

                        try {
                            String line = reader.readLine();

                            IntValue value = new IntValue(0);
                            if(line != null){
                                value.setValue(Integer.parseInt(line));
                            }
                            symbolsTable.put(this.variableName, value);
                        } catch (IOException e) {
                            throw new MyException(e.getMessage());
                        }
                    }
                    else{
                        throw new MyException("File is not defined");
                    }
                }
                else{
                    throw new MyException("Read requires a string");
                }
            }
            else {
                throw new MyException("Variable is not an integer");
            }
        }
        else {
            throw new MyException("Variable is not defined");
        }

        return null;
    }

    @Override
    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnvironment) throws MyException {
        IType expressionType = this.expression.typeCheck(typeEnvironment);
        IType variableType;
        try {
            variableType = typeEnvironment.lookup(this.variableName);
        }
        catch (MyException exception){
            throw new VariableNotDefined(this.variableName);
        }

        if(expressionType.equals(new StringType())){
            if(variableType.equals(new IntType())) {
                return typeEnvironment;
            }else {
                throw new MyException("Variable is not an integer");
            }
        }
        else{
            throw new MyException("Expression is not a string");
        }
    }

    @Override
    public ReadFileStatement deepCopy() {
        return new ReadFileStatement(this.expression.deepCopy(), this.variableName);
    }

    @Override
    public String toString() {
        return "readFile(" + this.expression.toString() + ", " + this.variableName + ");";
    }
}
