package Exceptions;

public class EmptyCollection extends Exception{
    EmptyCollection(){}

    public EmptyCollection(String message){
        super(message);
    }
}
