public class Cell {
    boolean isDirty, visited=false;
    int agentId;

    public Cell(boolean isDirty, int agentId) {
        this.isDirty = isDirty;
        this.agentId = agentId;
    }
}
