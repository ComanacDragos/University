package Model.Types;

import Model.Values.IntValue;

public class IntType implements IType{
    @Override
    public boolean equals(Object another) {
        return another instanceof IntType;
    }

    @Override
    public String toString() {
        return "int";
    }

    @Override
    public IntValue getDefaultValue() {
        return new IntValue(0);
    }
}
