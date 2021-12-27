public class UpdateMessage extends Message{
    Variable variable;
    int value;

    public UpdateMessage(Variable variable, int value) {
        this.variable = variable;
        this.value = value;
    }

    public Variable getVariable() {
        return variable;
    }

    public int getValue() {
        return value;
    }

    @Override
    public String toString() {
        return variable + " = " + value;
    }

    @Override
    public void action(DistributedSharedMemory sharedMemory) {
        sharedMemory.setVariable(variable, value);
    }
}
