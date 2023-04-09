import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class CleanerAgent extends Agent {
    private int id;
    private int rows, cols;
    private Position position = null;

    protected void setup() {
        Object[] args = getArguments();
        int x, y;
        if (args != null && args.length > 0) {
            x = Integer.parseInt((String) args[0]);
            y = Integer.parseInt((String) args[1]);
            id = Integer.parseInt((String) args[2]);
            rows = Integer.parseInt((String) args[3]);
            cols = Integer.parseInt((String) args[4]);
        } else {
            throw new RuntimeException("Agent did not receive parameters");
        }
        System.out.println("Setup agent " + id + " with parameters:"
                + " x: " + x
                + ", y: " + y
                + ", rows: " + rows
                + ", cols: " + cols
        );
        position = new Position(x, y);
        addBehaviour(new RandomMovementBehavior());
    }

    private class RandomMovementBehavior extends CyclicBehaviour {
        private List<Position> getNextPositions(){
            List<Position> positions = new ArrayList<>();
            for(int i=-1;i<=1;i++)
                for(int j=-1;j<=1;j++)
                    if(i!=0 && j!=0){
                        int new_x = position.x+i;
                        int new_y = position.y+j;
                        if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols)
                            positions.add(new Position(new_x, new_y));
                    }
            return positions;
        }

        public void action() {
            List<Position> nextPositions = getNextPositions();

            if(nextPositions.size() > 0){
                position = nextPositions.get(new Random().nextInt(nextPositions.size()));
                ACLMessage message = new ACLMessage(ACLMessage.INFORM);
                message.addReceiver(new AID("env", AID.ISLOCALNAME));
                message.setContent(position.toString());
                send(message);
            }

            try {
                Thread.sleep(new Random().nextInt(500) + 1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
}
