package app.actions;

import app.Agent;
import app.State;

public class CleanDirtAction extends Action{
    @Override
    public State execute(Agent a, State s) {
        s.cleanDirt(a.id, a.position);
        a.onDirt = false;
        return s;
    }

    @Override
    public String toString() {
        return "CLEAN";
    }
}
