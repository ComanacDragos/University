package Exceptions;

public class VariableNotDefined extends MyException{
    public VariableNotDefined(){
        super("Variable not defined");
    }

    public VariableNotDefined(String message){
        super(message);
    }
}
