package app;

import utils.Position;

import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Blackboard {
    private final Set<Position> positions = new HashSet<>();
    private final ReadWriteLock lock = new ReentrantReadWriteLock();

    public Set<Position> getPositions() {
        lock.readLock().lock();
        Set<Position> toReturnSet = new HashSet<>(positions);
        lock.readLock().unlock();
        return toReturnSet;
    }

    public void addPos(Position pos){
        lock.writeLock().lock();
        positions.add(pos);
        lock.writeLock().unlock();
    }
}
