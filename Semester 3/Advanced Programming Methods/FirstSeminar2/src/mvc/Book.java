package mvc;

public class Book implements Model {
    int pages;
    String name;

    public Book(int pages, String name)
    {
        this.pages = pages;
        this.name = name;
    }

    @Override
    public int getWeight() {
        return 20 * pages;
    }

    @Override
    public String toString() {
        return this.name;
    }
}
