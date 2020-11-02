package Model.Types;

import Model.Values.BoolValue;

public class BoolType implements IType{
    @Override
    public boolean equals(Object another) {
        return another instanceof BoolType;
    }

    @Override
    public String toString() {
        return "bool";
    }

    @Override
     public BoolValue getDefaultValue() {
        return new BoolValue(false);
    }
}
