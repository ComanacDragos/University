package Model.Statements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement{
    IExpression expression;
    String variable_name;

    public ReadFileStatement(IExpression expression, String variable_name) {
        this.expression = expression;
        this.variable_name = variable_name;
    }

    public IExpression getExpression() {
        return expression;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    public String getVariable_name() {
        return variable_name;
    }

    public void setVariable_name(String variable_name) {
        this.variable_name = variable_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();

        if(symbolsTable.isDefined(this.variable_name)) {
            IValue variableValue = symbolsTable.lookup(this.variable_name);

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
                            symbolsTable.put(this.variable_name, value);
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

        return state;
    }

    @Override
    public ReadFileStatement deepCopy() {
        return new ReadFileStatement(this.expression.deepCopy(), this.variable_name);
    }

    @Override
    public String toString() {
        return "readFile(" + this.expression.toString() + ", " + this.variable_name + ");";
    }
}
