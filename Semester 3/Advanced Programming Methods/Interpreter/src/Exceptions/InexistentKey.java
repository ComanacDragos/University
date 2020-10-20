package Exceptions;

public class InexistentKey extends MyException{
  public InexistentKey(){}

  public InexistentKey(String message){
      super(message);
  }
}
