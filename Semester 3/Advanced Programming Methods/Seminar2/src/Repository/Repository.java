package Repository;
import Model.*;

public interface Repository {
    void store(Item item);

    Item[] getItems();

    Item getItem(int i);
}
