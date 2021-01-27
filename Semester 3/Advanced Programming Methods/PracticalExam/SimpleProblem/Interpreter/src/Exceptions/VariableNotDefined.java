package Exceptions;

public class VariableNotDefined extends MyException{
    public VariableNotDefined(){
        super("Variable not defined");
    }

    public VariableNotDefined(String variable){
        super("Variable " + variable + " is not defined");
    }
}
