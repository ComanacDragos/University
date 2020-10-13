package mvc;

import mvc.Model.Model;

public class Repository {
    DynamicVector items;

    public Repository()
    {
        items = new DynamicVector();
    }

    public void store(Model item)
    {
        this.items.store(item);
    }

    public DynamicVector getItems() {
        return items;
    }
    
    public Model getItem(int i)
    {
        return this.items.getItem(i);
    }
}
