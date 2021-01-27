package Model.Statements.FileStatements;

import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.IStatement;
import Model.Types.IType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFileStatement implements IStatement {
    IExpression expression;

    public CloseReadFileStatement(IExpression expression) {
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
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnvironment) throws MyException {
        IType expressionType = this.expression.typeCheck(typeEnvironment);
        if(expressionType.equals(new StringType())){
            return typeEnvironment;
        }
        else{
            throw new MyException("Expression is not a string");
        }
    }

    @Override
    public CloseReadFileStatement deepCopy() {
        return new CloseReadFileStatement(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "closeReadFile(" + this.expression.toString() + ");";
    }
}
