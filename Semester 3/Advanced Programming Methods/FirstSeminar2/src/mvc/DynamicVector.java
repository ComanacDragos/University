package mvc;

import mvc.Model.Model;

public class DynamicVector {
    int size, capacity;
    Model items[];

    DynamicVector()
    {
        this.size = 0;
        this.capacity = 2;
        this.items = new Model[this.capacity];
    }

    public int getSize() {
        return size;
    }

    public Model getItem(int i)
    {
        if(i < 0 || i >= this.size)
            throw new ArrayIndexOutOfBoundsException("Bad index");
        return this.items[i];
    }

    public void store(Model item)
    {
        this.resize();
        this.items[this.size] = item;
        size += 1;
    }

    private void resize()
    {
        if(this.size == this.capacity)
        {
            this.capacity *= 2;

            Model[] newItems = new Model[this.capacity];

            for(int i=0; i<this.size; i+=1)
                newItems[i] = this.items[i];

            this.items = newItems;
        }
    }
}
