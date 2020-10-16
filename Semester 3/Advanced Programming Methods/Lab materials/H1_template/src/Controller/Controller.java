package Controller;

import Model.IVegetable;
import Repository.MyException;
import Repository.Repo;
import Repository.IRepo;

public class Controller{

    public  IRepo r = new Repo(10);

    public Controller(IRepo repo){
        this.r = repo;
    }
    public void add(IVegetable elem) throws MyException
    {
        r.add(elem);
    }
    public void remove(int pos) throws MyException
    {
        r.remove(pos);
    }
    public IRepo filter() throws MyException
    {
        Repo filteredRepo = new Repo(10);
        filteredRepo.data = r.filter();
        if(filteredRepo.data.length == 0)
        {
            throw new MyException("There are no vegetables with weight less than 0.2 kg.\n");
        }
        return filteredRepo;
    }
}