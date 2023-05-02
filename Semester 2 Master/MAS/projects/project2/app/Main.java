package app;

import utils.Cell;
import utils.GridGUI;
import utils.Position;

import java.util.HashSet;
import java.util.LinkedList;

public class Main {

    public static void main(String[] args) {
        int M = 3; // rows
        int N = 3; // cols
        int P = 25; // dirt percent
        int K = 1; // nr agents

        GridGUI gui = new GridGUI(M, N);
        Blackboard blackboard = new Blackboard();

        HashSet<Position> pairs = new HashSet<>();
        while(pairs.size() < K) {
            int x = (int) (Math.random() * N);
            int y = (int) (Math.random() * M);
            pairs.add(new Position(x, y));
        }

        State state = new State(M, N, P, K, gui);
        Environment env = new Environment(state);

        LinkedList<Simulation> simulations = new LinkedList<>();
        int id = 0;
        for(Position position: pairs){
            Agent agent = new Agent(id, K, M, N, position, blackboard);
            Simulation simulation = new Simulation(agent, env);
            simulation.start();
            simulations.add(simulation);
            id++;
        }

        for(Simulation simulation: simulations){
            try{
                simulation.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}

