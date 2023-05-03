package app;

import utils.Cell;
import utils.GridGUI;
import utils.Position;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class State {
    private final GridGUI gui;
    int nrAgents, nrDirty=0;
    Cell[][] grid;
    ReadWriteLock[][] locks;

    Map<Integer, Integer> scores = new ConcurrentHashMap<>();

    public State(int rows, int cols, int dirtyPercent, int nrAgents, GridGUI gui){
        grid = new Cell[rows][cols];
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++){
                boolean dirty = Math.random() * 100 < dirtyPercent;
                grid[i][j] = new Cell(dirty, -1);
                if(dirty)
                    nrDirty += 1;
            }
        gui.updateGrid(grid);
        locks = new ReentrantReadWriteLock[rows][cols];
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
                locks[i][j] = new ReentrantReadWriteLock();
        this.gui = gui;
        for(int i=0;i<nrAgents;i++)
            scores.put(i, 0);
    }

    private void readLockPos(Position position){
        ReadWriteLock lock = locks[position.y][position.x];
        lock.readLock().lock();
    }

    private void readUnlockPos(Position position){
        ReadWriteLock lock = locks[position.y][position.x];
        lock.readLock().unlock();
    }

    private void writeLockPos(Position position){
        ReadWriteLock lock = locks[position.y][position.x];
        lock.writeLock().lock();
    }

    private void writeUnlockPos(Position position){
        ReadWriteLock lock = locks[position.y][position.x];
        lock.writeLock().unlock();
    }

    private Cell positionToCell(Position position){
        return grid[position.y][position.x];
    }

    public boolean isDirty(Position position){
        readLockPos(position);
        boolean toReturn = grid[position.y][position.x].isDirty;
        readUnlockPos(position);
        return toReturn;
    }

    public void cleanDirt(int id, Position position){
        writeLockPos(position);
        Cell cell = positionToCell(position);
        cell.isDirty = false;
        gui.updateCell(position, cell);
        scores.put(id, scores.get(id) + 1);
        logScores();
        writeUnlockPos(position);
    }

    private synchronized void logScores(){
        int cleaned = scores.entrySet().stream().map(
                Map.Entry::getValue
        ).reduce(0, Integer::sum);

        System.out.println("\nSCORE " + cleaned + "/" + nrDirty);
        for(Map.Entry<Integer, Integer> entry : scores.entrySet()) {
            System.out.println(entry.getKey() + " -> " + entry.getValue());
        }
        System.out.println("\n");
    }

    public void spawnAgent(int id, Position position){
        Cell cell = positionToCell(position);
        cell.agentId = id;
        gui.updateCell(position, cell);
    }

    public Position moveAgent(int id, Position currentPos, Position desiredPos){
        boolean canMove = true;
        writeLockPos(currentPos);
        writeLockPos(desiredPos);
        Cell currentCell = positionToCell(currentPos);
        Cell desiredCell = positionToCell(desiredPos);
        if(desiredCell.agentId != -1)
            canMove = false;
        else {
            currentCell.agentId = -1;
            currentCell.visited = true;
            desiredCell.agentId = id;
            desiredCell.visited = true;
            gui.updateCell(currentPos, currentCell);
            gui.updateCell(desiredPos, desiredCell);
        }
        writeUnlockPos(desiredPos);
        writeUnlockPos(currentPos);
        //System.out.println(canMove + " " + (new Random()).nextInt());
        if(canMove)
            return desiredPos;
        return currentPos;
    }

    public void shutDownAgent(Position position){
        writeLockPos(position);
        Cell cell = positionToCell(position);
        cell.agentId = -1;
        cell.visited = true;
        gui.updateCell(position, cell);
        writeUnlockPos(position);
    }
}
