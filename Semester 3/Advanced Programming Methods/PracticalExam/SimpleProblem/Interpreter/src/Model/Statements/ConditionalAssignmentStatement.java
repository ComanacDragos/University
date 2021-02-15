package Model.Statements;

import Exceptions.MyException;
import Exceptions.VariableNotDefined;
import Model.ADTs.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Statements.ControlFlowStatements.IfStatement;
import Model.Types.BoolType;
import Model.Types.IType;

public class ConditionalAssignmentStatement implements IStatement{
    String variableName;
    IExpression conditionalExpression;
    IExpression thenExpression;
    IExpression elseExpression;

    public ConditionalAssignmentStatement(String variableName, IExpression conditionalExpression, IExpression thenExpression, IExpression elseExpression) {
        this.variableName = variableName;
        this.conditionalExpression = conditionalExpression;
        this.thenExpression = thenExpression;
        this.elseExpression = elseExpression;
    }

    public String getVariableName() {
        return variableName;
    }

    public void setVariableName(String variableName) {
        this.variableName = variableName;
    }

    public IExpression getConditionalExpression() {
        return conditionalExpression;
    }

    public void setConditionalExpression(IExpression conditionalExpression) {
        this.conditionalExpression = conditionalExpression;
    }

    public IExpression getThenExpression() {
        return thenExpression;
    }

    public void setThenExpression(IExpression thenExpression) {
        this.thenExpression = thenExpression;
    }

    public IExpression getElseExpression() {
        return elseExpression;
    }

    public void setElseExpression(IExpression elseExpression) {
        this.elseExpression = elseExpression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        state.getExecutionStack().push(
                new IfStatement(
                        this.conditionalExpression,
                        new AssignStatement(this.variableName, this.thenExpression),
                        new AssignStatement(this.variableName, this.elseExpression)
                )
        );
        return null;
    }

    @Override
    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnvironment) throws MyException {
        IType condType = this.conditionalExpression.typeCheck(typeEnvironment);
        if(condType.equals(new BoolType())){
            if(typeEnvironment.isDefined(this.variableName)){
                IType varType = typeEnvironment.lookup(this.variableName);
                IType thenType = this.thenExpression.typeCheck(typeEnvironment);
                if(varType.equals(thenType)){
                    IType elseType = this.elseExpression.typeCheck(typeEnvironment);
                    if(!varType.equals(elseType)){
                        throw new MyException("Variable and else expression must have the same typ");
                    }
                }else{
                    throw new MyException("Variable and then expression must have the same type");
                }
            }else{
                throw new VariableNotDefined(this.variableName);
            }
        }else{
            throw new MyException("Condition must be a boolean");
        }
        return typeEnvironment;
    }

    @Override
    public IStatement deepCopy() {
        return new ConditionalAssignmentStatement(this.variableName, this.conditionalExpression.deepCopy(), this.thenExpression.deepCopy(), this.elseExpression.deepCopy());
    }

    @Override
    public String toString() {
        return this.variableName + "=(" +this.conditionalExpression + ")?" + this.thenExpression + ":" + this.elseExpression;
    }
}
