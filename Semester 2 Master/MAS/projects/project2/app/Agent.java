package app;

import app.actions.*;
import utils.Position;

import java.util.*;

public class Agent {
    public int id, nrAgents;
    private int rows, cols;
    public Position position;

    private Deque<Position> previousPositions = new ArrayDeque<>();
    private Blackboard blackboard;
    public boolean isSpawned= false;
    public boolean onDirt = false;
    private boolean isOver = false;

    public Agent(int id, int nrAgents, int rows, int cols, Position position, Blackboard blackboard) {
        this.id = id;
        this.nrAgents = nrAgents;
        this.rows = rows;
        this.cols = cols;
        this.position = position;
        this.blackboard = blackboard;
        blackboard.addPos(position);

        System.out.println("Setup agent " + id + " with parameters:"
                + " position: " + position
                + ", rows: " + rows
                + ", cols: " + cols
                + ", nrAgents: " + nrAgents
        );
    }

    public void moveAgent(Position newPos){
        if(position.equals(newPos))
            return;

        if(!previousPositions.isEmpty() && previousPositions.peek().equals(newPos))
            previousPositions.pop();
        else
            previousPositions.push(position);

        this.position = newPos;
        blackboard.addPos(newPos);
    }


    public void see(Percept p) {
        if(Objects.isNull(p)){
            return;
        }
        onDirt = p.isDirty;
    }

    private List<Position> getNextPositions(){
        List<Position> positions = new ArrayList<>();
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++)
                if(!(i==0 && j==0)){
                    int new_x = position.x+i;
                    int new_y = position.y+j;
                    if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols) {
                        positions.add(new Position(new_x, new_y));
                    }
                }
        return positions;
    }

    private List<Position> filterNextPositions(List<Position> positions){
        List<Position> filtered = new LinkedList<>();
        for(Position position: positions)
            if(!blackboard.getPositions().contains(position))
                filtered.add(position);

        if(filtered.isEmpty() && !previousPositions.isEmpty())
            filtered.add(previousPositions.peek());
        return filtered;
    }

    public Action selectAction() {
        if(!isSpawned) {
            isSpawned = true;
            return new SpawnAgentAction();
        }
        if (blackboard.getPositions().size() == rows*cols && !onDirt) {
            isOver = true;
            return new ShutDownAction();
        }

        if (onDirt)
            return new CleanDirtAction();

        List<Position> nextPositions = filterNextPositions(getNextPositions());
        if(nextPositions.size() == 0)
            return null;
        Collections.shuffle(nextPositions);
        return new MoveAction(nextPositions.get(0));
    }

    public boolean isOver(){
        return isOver;
    }
}
