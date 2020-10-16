package Exceptions;

public class MyException extends Exception{
    protected String message;

    MyException(){}

    MyException(String message){
        super(message);
    }

    @Override
    public String toString(){
        return this.message;
    }
}
