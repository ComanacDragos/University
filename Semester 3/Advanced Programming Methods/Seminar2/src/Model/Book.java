package Model;

public class Book implements Item{
    int pages;
    String name;

    public Book(int pages, String name) {
        this.pages = pages;
        this.name = name;
    }

    @Override
    public int getWeight() {
        return this.pages*2;
    }

    @Override
    public String toString() {
        return this.name + " " + this.getWeight();
    }
}
