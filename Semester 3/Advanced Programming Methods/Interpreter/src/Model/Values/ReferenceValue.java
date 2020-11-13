package Model.Values;

import Model.Types.IType;
import Model.Types.ReferenceType;

public class ReferenceValue implements IValue{
    int address;
    IType locationType;

    public ReferenceValue(IType locationType){
        this.address = 0;
        this.locationType = locationType;
    }

    public ReferenceValue(int address, IType locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    @Override
    public IType getType() {
        return new ReferenceType(this.locationType);
    }

    public int getAddress() {
        return address;
    }

    public void setAddress(int address) {
        this.address = address;
    }

    public IType getLocationType() {
        return locationType;
    }

    public void setLocationType(IType locationType) {
        this.locationType = locationType;
    }

    @Override
    public IValue deepCopy() {
        return new ReferenceValue(this.address, this.locationType);
    }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof ReferenceValue))
            return false;
        ReferenceValue value = (ReferenceValue) obj;

        return this.address == value.getAddress() && this.locationType.equals(value.locationType);
    }

    @Override
    public String toString() {
        return "(" + this.address + ", " + this.locationType.toString() + ")";
    }
}
