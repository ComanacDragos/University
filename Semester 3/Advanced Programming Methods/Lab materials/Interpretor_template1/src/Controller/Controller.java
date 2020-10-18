package Controller;
import Model.PrgState;
import Repo.Repo;

public class Controller {

    //constructor

    public void addProgram(PrgState newPrg) {
        Repo.addPrg(newPrg);
    }

    public PrgState oneStep(PrgState state){...}

    public void allStep(){...}
}
