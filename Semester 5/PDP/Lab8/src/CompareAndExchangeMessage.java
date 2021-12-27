public class CompareAndExchangeMessage extends Message{
    Variable variable;
    int oldValue, newValue;

    public CompareAndExchangeMessage(Variable variable, int oldValue, int newValue) {
        this.variable = variable;
        this.oldValue = oldValue;
        this.newValue = newValue;
    }

    public Variable getVariable() {
        return variable;
    }

    public int getOldValue() {
        return oldValue;
    }

    public int getNewValue() {
        return newValue;
    }

    @Override
    public String toString() {
        return variable + " ? " + oldValue + " = " + newValue;
    }

    @Override
    public void action(DistributedSharedMemory sharedMemory) {
        sharedMemory.setVariable(variable, newValue);
    }
}
