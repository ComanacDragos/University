package app;

public class Percept {
    public boolean isDirty = false;

    public Percept(State state, Agent agent){
        isDirty = state.isDirty(agent.position);
    }

    @Override
    public String toString() {
        return "PERCEPT: " + isDirty;
    }
}
