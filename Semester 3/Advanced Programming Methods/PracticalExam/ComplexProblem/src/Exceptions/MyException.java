package Exceptions;

public class MyException extends RuntimeException{
    protected String message;

    public MyException(){}

    public MyException(String message){
        super(message);
        this.message = message;
    }

    @Override
    public String toString(){
        return this.message;
    }
}
