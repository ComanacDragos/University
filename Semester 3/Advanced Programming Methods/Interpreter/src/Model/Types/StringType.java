package Model.Types;

import Model.Values.IValue;
import Model.Values.StringValue;

public class StringType implements IType{

    @Override
    public boolean equals(Object obj) {
        return obj instanceof StringType;
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
