package app.actions;

import app.Agent;
import app.State;

public class SpawnAgentAction extends Action{
    @Override
    public State execute(Agent a, State s) {
        s.spawnAgent(a.id, a.position);
        return s;
    }

    @Override
    public String toString() {
        return "spawn agent";
    }
}