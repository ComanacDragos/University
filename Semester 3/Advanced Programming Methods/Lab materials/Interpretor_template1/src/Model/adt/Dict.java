package Model.adt;
import java.util.HashMap;

public class Dict<T1,T2> implements Dict<T1,T2> {
    HashMap<T1, T2> dictionary;

    public Dict() {
        dictionary = new HashMap<T1,T2>();
    }


}
