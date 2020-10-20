package Exceptions;

public class EmptyCollection extends Exception{
    public EmptyCollection(){}

    public EmptyCollection(String message){
        super(message);
    }


}
