package Repository;

import Model.Item;

public class InMemoryRepository implements Repository{
    Item[] items;

    InMemoryRepository(){
        this.items = new Item[100];
    }

    @Override
    public void store(Item item) {

    }

    @Override
    public Item[] getItems() {
        return new Item[0];
    }

    @Override
    public Item getItem(int i) {
        return null;
    }
}
