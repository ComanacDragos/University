public class Main {
    public static void main(String[] args) {
        test();

    }

    public static void runAll(){
        //generatePolynomials(10000, 10000);
        run("regular", 1);
        System.out.println("done regular");
        run("karatsuba", 1);
    }

    public static void test(){
        generatePolynomials(6, 6);
        Polynomial p = new Polynomial("data/p1.txt");
        Polynomial q = new Polynomial("data/p2.txt");
        System.out.println(p);
        System.out.println(q);

        System.out.println("===================");
        System.out.println(SequentialRegularMultiplier.multiply(p, q));
        System.out.println(SequentialKaratsubaMultiplier.multiply(p, q));
        System.out.println(ParalelRegularSolver.multiply(p, q, 4));
        System.out.println("===================");

        System.out.println(SequentialAdder.add(p, q, 1));
        System.out.println(SequentialAdder.add(p, p, 1));
        System.out.println(SequentialAdder.add(q, q, 1));
    }

    public static void run(String variant, int threads){
        Polynomial p1 = new Polynomial("data/p1.txt");
        Polynomial p2 = new Polynomial("data/p2.txt");
        double mean = 0.0;
        for (int i = 0; i < 10; i++) {
            long start = System.currentTimeMillis();
            if(variant.equals("regular"))
                mean += regular(threads, p1, p2);
            else
                mean += karatsuba(threads, p1, p2);
        }
        Logger.log(mean/10.0, threads, variant, p1.degree, p2.degree);
    }

    public static double regular(int nrThreads, Polynomial p1, Polynomial p2){
        long start = System.currentTimeMillis();
        if(nrThreads==1)
            SequentialRegularMultiplier.multiply(p1, p2);
        else
            ParalelRegularSolver.multiply(p1, p2, nrThreads);
        return System.currentTimeMillis() - start;
    }

    public static double karatsuba(int nrThreads, Polynomial p1, Polynomial p2){
        long start = System.currentTimeMillis();
        if(nrThreads==1)
            SequentialKaratsubaMultiplier.multiply(p1, p2);
        return System.currentTimeMillis() - start;
    }

    public static void generatePolynomials(int degree1, int degree2){
        new Polynomial(degree1, "data/p1.txt");
        new Polynomial(degree2, "data/p2.txt");
    }
}
