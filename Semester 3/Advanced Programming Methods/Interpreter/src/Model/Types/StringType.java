package Model.Types;

import Model.Values.StringValue;

public class StringType implements IType{

    @Override
    public boolean equals(Object another) {
        return another instanceof StringType;
    }

    @Override
    public String toString() {
        return "string";
    }

    @Override
    public StringValue getDefaultValue() {
        return new StringValue("");
    }
}
