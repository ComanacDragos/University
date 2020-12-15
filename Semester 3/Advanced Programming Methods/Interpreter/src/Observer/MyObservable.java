package Observer;

import java.util.LinkedList;
import java.util.List;

public class MyObservable {
    List<MyObserver> myObserverList = new LinkedList<>();
    
    public void addObserver(MyObserver myObserver){
        this.myObserverList.add(myObserver);
    }

    public void removeObserver(MyObserver myObserver){
        this.myObserverList.remove(myObserver);
    }

    public void notyfiObservers(){
        this.myObserverList.forEach(MyObserver::update);
    }
}
