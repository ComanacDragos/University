package Model.Values;

import Model.Types.IType;
import Model.Types.StringType;

public class StringValue implements IValue{
    String value;

    public StringValue(){
        this.value = (new StringType()).getDefaultValue().getValue();
    }

    public StringValue(String value){
        this.value = value;
    }

    public String getValue(){
        return this.value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public StringValue deepCopy() {
        return new StringValue(this.value);
    }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof StringValue))
            return false;
        return this.value.equals(((StringValue) obj).getValue());
    }

    @Override
    public String toString() {
        return '"' + this.value + '"';
    }
}
