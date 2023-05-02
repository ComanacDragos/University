package app;


import app.actions.Action;

public class Environment {
    public State state;

    public Environment(State state){
        this.state = state;
    }

    public void updateState(Agent a, Action action) {
        state = action.execute(a, state);
    }


    public Percept getPercept(Agent a) {
        if(!a.isSpawned)
            return null;
        return new Percept(state, a);
    }
}
