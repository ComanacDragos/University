package utils;

public class Cell {
    public boolean isDirty, visited=false;
    public int agentId;

    public Cell(boolean isDirty, int agentId) {
        this.isDirty = isDirty;
        this.agentId = agentId;
    }
}
