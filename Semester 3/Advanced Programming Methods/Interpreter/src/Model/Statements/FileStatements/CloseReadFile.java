package Model.Statements.FileStatements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFile implements IStatement {
    IExpression expression;

    public CloseReadFile(IExpression expression) {
        this.expression = expression;
    }

    public IExpression getExpression() {
        return expression;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, BufferedReader> fileTable = state.getFileTable();
        IValue value = this.expression.eval(state.getSymbolsTable(), state.getHeap());

        if(value.getType().equals(new StringType())){
            StringValue fileName = (StringValue)value;

            if(fileTable.isDefined(fileName.getValue())){
                try{
                    fileTable.lookup(fileName.getValue()).close();
                    fileTable.remove(fileName.getValue());
                } catch (IOException e) {
                    throw new MyException(e.getMessage());
                }
            }
            else{
                throw new MyException("File is not defined");
            }
        }
        else{
            throw new MyException("Close requires a string");
        }
        return state;
    }

    @Override
    public CloseReadFile deepCopy() {
        return new CloseReadFile(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "closeReadFile(" + this.expression.toString() + ");";
    }
}
