import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        //test();
        runAll();
    }

    public static void runAll(){
        generatePolynomials(10000, 10000);
       Arrays.asList(1, 2, 4, 8, 16).forEach(noThreads ->{
           run("regular", noThreads);
           System.out.println("done regular with " + noThreads);
           run("karatsuba", noThreads);
           System.out.println("done karatsuba with " + noThreads);
        });

    }

    public static void test(){
        generatePolynomials(10000, 10000);
        PolynomialImpl p = new PolynomialImpl("data/p1.txt");
        PolynomialImpl q = new PolynomialImpl("data/p2.txt");
        System.out.println(p);
        System.out.println(q);

        System.out.println("===================");
        String r1,r2,r3,r4;
        long start = System.currentTimeMillis();
        r1 = SequentialRegularMultiplier.multiply(p, q).toString();
        System.out.println("done regular seq");
        r2 = SequentialKaratsubaMultiplier.multiply(p, q).toString();
        System.out.println("done karatsuba seq");
        r3 = ParalelRegularSolver.multiply(p, q, 4, ParalelRegularSolver.splitTasks(p.getDegree(), q.getDegree(), 4)).toString();
        System.out.println("done regular parallel");
        r4 = ParalelKaratsubaSolver.multiply(p, q, 8).toString();
        System.out.println("done karatsuba parallel");
        System.out.println(System.currentTimeMillis()-start);
        //System.out.println(r1);
        //System.out.println(r3);

        //System.out.println(r2);
        //System.out.println(r4);
        System.out.println(r1.equals(r2));
        System.out.println(r2.equals(r3));
        System.out.println(r3.equals(r4));
        System.out.println("===================");

        //System.out.println(SequentialAdder.add(p, q, 1));
        //System.out.println(SequentialAdder.add(p, p, 1));
        //System.out.println(SequentialAdder.add(q, q, 1));
    }

    public static void run(String variant, int threads){
        PolynomialImpl p1 = new PolynomialImpl("data/p1.txt");
        PolynomialImpl p2 = new PolynomialImpl("data/p2.txt");
        double mean = 0.0;
        for (int i = 0; i < 10; i++) {
            if(variant.equals("regular"))
                mean += regular(threads, p1, p2);
            if(variant.equals("karatsuba"))
                mean += karatsuba(threads, p1, p2);
        }
        Logger.log(mean/10.0, threads, variant, p1.degree, p2.degree);
    }

    public static double regular(int noThreads, PolynomialImpl p, PolynomialImpl q){
        long start = System.currentTimeMillis();
        if(noThreads==1)
            SequentialRegularMultiplier.multiply(p, q);
        else{
            List<List<Integer>> splitTasks = ParalelRegularSolver.splitTasks(p.getDegree(), q.getDegree(), noThreads);
            start = System.currentTimeMillis();
            ParalelRegularSolver.multiply(p, q, noThreads, splitTasks);
        }
        return System.currentTimeMillis() - start;
    }

    public static double karatsuba(int noThreads, PolynomialImpl p, PolynomialImpl q){
        long start = System.currentTimeMillis();
        if(noThreads==1)
            SequentialKaratsubaMultiplier.multiply(p, q);
        else
            ParalelKaratsubaSolver.multiply(p, q, noThreads);
        return System.currentTimeMillis() - start;
    }

    public static void generatePolynomials(int degree1, int degree2){
        new PolynomialImpl(degree1, "data/p1.txt");
        new PolynomialImpl(degree2, "data/p2.txt");
    }
}
