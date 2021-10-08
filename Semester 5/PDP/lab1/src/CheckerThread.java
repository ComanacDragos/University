import java.util.concurrent.atomic.AtomicBoolean;

public class CheckerThread extends Thread {
    public Logger logger = new Logger("CheckThread");
    Inventory inventory;
    AtomicBoolean isFinished;

    public CheckerThread(Inventory inventory, AtomicBoolean isFinished) {
        this.inventory = inventory;
        this.isFinished = isFinished;
    }

    @Override
    public void run(){
        try {
            while (!isFinished.get()){
                inventory.inventoryCheck("thread");
                Thread.sleep(10);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
