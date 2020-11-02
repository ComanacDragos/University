package Model.Values;

import Model.Types.BoolType;
import Model.Types.IType;

public class BoolValue implements IValue{
    boolean value;

    public BoolValue(boolean value){
        this.value = value;
    }

    public BoolValue(){
        this.value = (new BoolType()).getDefaultValue().getValue();
    }


    public boolean getValue(){
        return this.value;
    }

    public void setValue(boolean value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }
}
