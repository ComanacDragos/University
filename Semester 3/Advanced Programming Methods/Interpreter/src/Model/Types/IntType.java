package Model.Types;

public class IntType implements IType{
    @Override
    public boolean equals(Object another) {
        return another instanceof IntType;
    }

    @Override
    public String toString() {
        return "int";
    }
}
