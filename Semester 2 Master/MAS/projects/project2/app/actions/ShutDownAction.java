package app.actions;

import app.Agent;
import app.State;

public class ShutDownAction extends Action{
    @Override
    public State execute(Agent a, State s) {
        s.shutDownAgent(a.position);
        return s;
    }

    @Override
    public String toString() {
        return "SHUT DOWN";
    }
}
