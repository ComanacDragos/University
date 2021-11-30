import java.util.*;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        //testGraph();
        //new DirectedGraph(20, 80);
        //testSequential();
        //testParallel();
        runAll();
    }

    public static void runAll() {
        DirectedGraph graph = new DirectedGraph("data/20_80.txt");
        Arrays.asList(1, 2, 4, 8, 16).forEach(noThreads -> {
            run(graph, noThreads);
            System.out.println("done with " + noThreads);
        });

    }

    public static void run(DirectedGraph graph, int threads){
        double mean = 0.0;
        for (int i = 0; i < 10; i++) {
            Solver solver;
            if(threads == 1) {
                solver = new SequentialSolver(graph);
            }else{
                solver = new ParallelSolver(graph, threads);
            }
            long start = System.nanoTime();
            List<List<Integer>> solutions = solver.solve();
            mean += System.nanoTime()-start;
        }
        Logger.log((mean/10.0)/1000000.0, threads, graph.getNoVertices(), graph.getNoEdges());
    }

        //20_80
    public static void testSequential(){
        System.out.println("starting sequential");
        DirectedGraph graph = new DirectedGraph("data/20_80.txt");
        SequentialSolver solver = new SequentialSolver(graph);
        long start = System.currentTimeMillis();
        List<List<Integer>> solutions = solver.solve();
        System.out.println("Time: " + (System.currentTimeMillis()-start));
        if(solutions.size() == 0)
            System.out.println("No solution");
        else{
            System.out.println(solutions.size());
            //solutions.forEach(System.out::println);
            validateResults(graph, solutions);
        }
    }

    public static void testParallel(){
        System.out.println("starting parallel");
        DirectedGraph graph = new DirectedGraph("data/20_80.txt");
        ParallelSolver solver = new ParallelSolver(graph, 4);
        long start = System.currentTimeMillis();
        List<List<Integer>> solutions = solver.solve();
        System.out.println("Time: " + (System.currentTimeMillis()-start));
        if(solutions.size() == 0)
            System.out.println("No solution");
        else{
            System.out.println(solutions.size());
            //solutions.forEach(System.out::println);
            validateResults(graph, solutions);
        }
    }

    public static void validateResults(DirectedGraph graph, List<List<Integer>> results){
        results.forEach(result ->{
            if(!result.get(0).equals(0) || !result.get(result.size()-1).equals(0))
                System.out.println("Bad start and end " + result);
            if(result.size() - 1 != (new HashSet<>(result).size()))
                System.out.println("Bad sizes " + result);
            for(int i=0;i<result.size()-1;i++){
                Integer x = result.get(i), y = result.get(i+1);
                if(!graph.isEdge(x, y)){
                    System.out.println("No edge between " + x + " - " + y + " ! " + result);
                }
            }
        });
    }

    public static void testGraph(){
        DirectedGraph graph = new DirectedGraph("data/Example.txt");
        graph.getDictOut().entrySet().forEach(
                entry -> System.out.println(entry.getKey() + " -> " + entry.getValue())
        );
    }
}
