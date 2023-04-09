import jade.Boot;

import java.util.HashSet;

public class Main {

    public static void main(String[] args) {
        int M = 10;
        int N = 10;
        int P = 5;
        int K = 1;

        String agents = "env:" + GridEnvironment.class.getName() + "(" + M + "," + N + "," + P + ")";

        HashSet<String> pairs = new HashSet<>();
        while(pairs.size() < K) {
            int x = (int) (Math.random() * N);
            int y = (int) (Math.random() * M);
            pairs.add(x+","+y);
        }

        int id = 0;
        for(String pair: pairs){
            agents += ";a" + id + ":" + CleanerAgent.class.getName() + "(" + pair + "," + id + "," + M + "," + N + ")";
            id ++;
        }
        System.out.println(agents);
        Boot.main(new String[]{
                //"-gui",
                "-agents",
                agents
        });
    }

}
