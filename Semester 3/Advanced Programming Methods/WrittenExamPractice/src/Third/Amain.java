package Third;

import java.util.ArrayList;

public class Amain {
    A method1(ArrayList<? extends A> list){
        if(list.isEmpty()) return null;
        else
            return list.get(1);
    }

    void method2(ArrayList<? extends A> list){
        list.add(null);
    }

    void method3(){
        ArrayList<A> listA = new ArrayList<>();
        listA.add(new A());
        listA.add(new A());

        ArrayList<B> listB = new ArrayList<>();
        listB.add(new B());
        listB.add(new B());

        ArrayList<C> listC = new ArrayList<>();
        listC.add(new C());
        listC.add(new C());

        this.method1(listA);
        this.method1(listB);
        this.method1(listC);

        this.method2(listA);
        this.method2(listB);
        this.method2(listC);
    }
}
