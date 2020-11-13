package Model.Types;

import Model.Values.IValue;
import Model.Values.ReferenceValue;

public class ReferenceType implements IType{
    IType innerType;

    public ReferenceType(IType innerType) {
        this.innerType = innerType;
    }

    public IType getInnerType() {
        return innerType;
    }

    @Override
    public boolean equals(Object another) {
        if(another instanceof ReferenceType)
            return this.innerType.equals(((ReferenceType) another).getInnerType());
        return false;
    }

    @Override
    public String toString() {
        return "ref(" + this.innerType.toString() + ")" ;
    }

    @Override
    public IValue getDefaultValue() {
        return new ReferenceValue(0, this.innerType);
    }
}
