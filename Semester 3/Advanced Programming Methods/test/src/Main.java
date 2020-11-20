import java.util.HashSet;
import java.util.Set;
//
//
//interface JavaInterface{
//    protected int x = 10;
//    int y;
//    int z=20;
//    default
//    int x(){
//        return 0;
//    }
//
//    abstract void foo();
//    final int f(int x);
//}

//
//
//public class Main{
//
//}
//
//class Shape{
//    public String type = " s ";
//    public Shape(){
//        System.out.print("shape ");
//    }
//}
//
//class Rectangle extends Shape{
//    public Rectangle(){System.out.print("rectangle ");}
//
//    public static void main(String[] args) {
//        new Rectangle().go();
//    }
//
//    void go(){
//        type = "r ";
//        System.out.print(this.type + super.type);
//    }
//}
//
//
//
//
//
//public class Main{
//    Integer a= 10;
//    public int f(int x, int y)throws Exception{
//        if(x*y<0)
//            throw new Exception();
//        return x+y;
//    }
//
//    public int g(int x, int y){
//        try{
//            a = f(x,y);
//            return a;
//        }
//        catch (Exception ne){
//            a = a*a+1;
//            return a;
//        }
//        finally {
//            a = a*a;
//            return a+1;
//        }
//    }
//
//    public static void main(String[] args) {
//        System.out.println(new Main().g(1, -1));
//    }
//}


//class A{
//    protected int computeX(int a, float b){
//        return 1;
//    }
//}
//
//class B extends A{
//    @Override
//    protected Integer computeX(int a, float b) {
//        return super.computeX(a, b);
//    }
//}



//
//class Main{
//    public static void main(String[] args) {
//        //HashSet<Integer> set  = new Set<Integer>();
//        //Set<Integer> set = new HashSet<Integer>();
//
//        //HashSet<Object> set = new HashSet<Integer>();
//
//        //Set<Integer> set = new HashSet<Object>();
//    }
//}


//
//class A{
//    public static boolean val;
//    public A(){
//        val = true;
//    }
//    public static void print(){
//        System.out.println("First");
//    }
//}
//
//public class Main{
//    public static void main(String[] args) {
//        A a = null;
//        if(!a.val)a.print();
//        else System.out.println("Second");
//    }
//}








//abstract class Abstract{
//    private int val;
//    Abstract(){val = 10;}
//    public void set(int val){
//        this.val = val + getValue();
//    }
//    public abstract int getValue();
//    public int get() {return val;}
//}
//
//class Main extends Abstract{
//    public int getValue(){
//        return 1111;
//    }
//
//    public static void main(String[] args) {
//        Main obj = new Main();
//        obj.set(11);
//        System.out.println(obj.get());
//    }
//}


class Main{
    public static void main(String[] args) {
        try{
            throw 78;
        }
        catch (int e){
            System.out.println("sdas");
        }
    }
}