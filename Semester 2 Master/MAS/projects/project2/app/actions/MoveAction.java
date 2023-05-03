package app.actions;

import app.Agent;
import app.State;
import utils.Position;

public class MoveAction extends Action{
    Position desiredPosition;
    public MoveAction(Position desiredPosition){
        this.desiredPosition = desiredPosition;
    }

    @Override
    public State execute(Agent a, State s) {
        a.moveAgent(s.moveAgent(a.id, a.position, desiredPosition));
        return s;
    }

    @Override
    public String toString() {
        return "MOVE";
    }
}
