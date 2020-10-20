package Model.Statements;

import Exceptions.DivisionByZero;
import Exceptions.MyException;
import Model.ADTs.MyIDictionary;
import Model.ADTs.MyIStack;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Types.IType;
import Model.Values.IValue;

public class AssignStatement implements IStatement{
    String id;
    IExpression expression;

    public AssignStatement(String id, IExpression expression){
        this.id = id;
        this.expression = expression;
    }

    public IExpression getExpression() {
        return expression;
    }

    public String getId() {
        return id;
    }

    public void setExpression(IExpression expression) {
        this.expression = expression;
    }

    public void setId(String id) {
        this.id = id;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException, DivisionByZero {
        MyIDictionary<String, IValue> symbolsTable = state.getSymbolsTable();

        if(symbolsTable.isDefined(this.id)){
            IValue value = this.expression.eval(symbolsTable);
            IType typeId = (symbolsTable.lookup(this.id)).getType();

            if(value.getType().equals(typeId))
                symbolsTable.update(this.id, value);
            else throw  new MyException("Declared type of variable " + id + " and type of the assigned expression do not match");
        }
        else
            throw new MyException("The used variable " + id + " was not declared before");

        return state;
    }

    @Override
    public String toString() {
        return this.id + "=" + this.expression.toString();
    }
}
