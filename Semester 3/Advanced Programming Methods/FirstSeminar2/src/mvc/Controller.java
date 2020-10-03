package mvc;

public class Controller {
    Repository repo;

    public Controller(Repository repo)
    {
        this.repo = repo;
    }

    public DynamicVector itemsHeavierThan(int grams)
    {
        DynamicVector items = new DynamicVector();

        for(int i=0;i <this.repo.items.getSize();i+=1)
            if(this.repo.getItem(i).getWeight() >= grams)
                items.store(this.repo.getItem(i));
        return items;
    }
}
