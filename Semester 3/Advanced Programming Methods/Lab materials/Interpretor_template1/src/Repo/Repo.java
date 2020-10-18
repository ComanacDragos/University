package Repo;
import Model.PrgState;
import Model.adt.List;

public class Repo implements IRepo {

    List<PrgState> myPrgStates;

    public Repo() {
        myPrgStates = new List<PrgState>();
    }

    @Override
    public PrgState getCrtPrg() {
        return myPrgStates.pop();
    }

    @Override
    public void addPrg(PrgState newPrg) {
        myPrgStates.add(newPrg);
    }
}
