package app;

import app.actions.Action;

import java.util.Objects;
import java.util.Random;

public class Simulation extends Thread{
    Agent agent;
    Environment env;

    public Simulation(Agent agent, Environment environment) {
        this.agent = agent;
        this.env = environment;
    }

    @Override
    public void run() {
        while (!isComplete()) {
            Percept p = env.getPercept(agent);
            agent.see(p);
            Action action = agent.selectAction();
            if(Objects.isNull(action))
                continue;
            env.updateState(agent, action);
        }
    }

    protected boolean isComplete() {
        if (env.state.nrCleaned == env.state.nrDirty)
            return true;
        else
            return false;
    }
}
