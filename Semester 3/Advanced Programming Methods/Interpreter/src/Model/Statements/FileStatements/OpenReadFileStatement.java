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
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenReadFileStatement implements IStatement {
    IExpression expression;

    public OpenReadFileStatement(IExpression expression){
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
        IValue expressionValue = this.expression.eval(state.getSymbolsTable(), state.getHeap());

        if(expressionValue.getType().equals(new StringType())){
            StringValue fileName = (StringValue) expressionValue;

            if(!fileTable.isDefined(fileName.getValue())){
                try{
                    BufferedReader reader = new BufferedReader(new FileReader(fileName.getValue()));
                    fileTable.put(fileName.getValue(), reader);
                } catch (FileNotFoundException e) {
                    throw new MyException(e.getMessage());
                }
            }
            else{
                throw new MyException("File is already open");
            }
        }
        else {
            throw new MyException("Open requires a string");
        }
        return null;
    }

    @Override
    public OpenReadFileStatement deepCopy() {
        return new OpenReadFileStatement(this.expression.deepCopy());
    }

    @Override
    public String toString() {
        return "openReadFile(" + this.expression.toString() + ");";
    }
}
