package Model.Values;

import Model.Types.IType;
import Model.Types.IntType;

public class IntValue implements IValue{
    int value;

    public IntValue(){
        this.value = 0;
    }

    public IntValue(int value){
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new IntType();
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }
}
