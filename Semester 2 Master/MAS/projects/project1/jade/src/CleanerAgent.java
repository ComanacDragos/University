import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;
import jade.core.behaviours.OneShotBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;

import java.util.*;

public class CleanerAgent extends Agent {
    private int id, nrAgents;
    private int rows, cols;
    private Position position = null;
    private Set<Position> cleanedCells = new HashSet<>();
    private Deque<Position> previousPositions = new ArrayDeque<>();

    protected void setup() {
        Object[] args = getArguments();
        int x, y;
        if (args != null && args.length > 0) {
            x = Integer.parseInt((String) args[0]);
            y = Integer.parseInt((String) args[1]);
            id = Integer.parseInt((String) args[2]);
            rows = Integer.parseInt((String) args[3]);
            cols = Integer.parseInt((String) args[4]);
            nrAgents = Integer.parseInt((String) args[5]);
        } else {
            throw new RuntimeException("Agent did not receive parameters");
        }
        System.out.println("Setup agent " + id + " with parameters:"
                + " x: " + x
                + ", y: " + y
                + ", rows: " + rows
                + ", cols: " + cols
                + ", nrAgents: " + nrAgents
        );
        position = new Position(x, y);

        addBehaviour(new CommunicateInitialPosition());
        addBehaviour(new CleaningBehaviour());
        addBehaviour(new ReceivePositionBehaviour());
        addBehaviour(new CheckIfOverBehaviour());
        addBehaviour(new MovementBehaviour());
    }

    private static void sleep(int ms){
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    MessageTemplate requestTemplate = MessageTemplate.MatchPerformative(ACLMessage.REQUEST);
    MessageTemplate confirmTemplate = MessageTemplate.MatchPerformative(ACLMessage.CONFIRM);
    MessageTemplate informTemplate = MessageTemplate.MatchPerformative(ACLMessage.INFORM);
    MessageTemplate agreeTemplate = MessageTemplate.MatchPerformative(ACLMessage.AGREE);


    private class CheckIfOverBehaviour extends CyclicBehaviour{
        @Override
        public void action(){
            if(cleanedCells.size() == rows*cols){
                ACLMessage message = new ACLMessage(ACLMessage.CANCEL);
                message.addReceiver(new AID("env", AID.ISLOCALNAME));
                message.setContent(id + "," + position);
                send(message);

                System.out.println(id + ": exiting...");
                doDelete();
            }
        }
    }

    private class ReceivePositionBehaviour extends CyclicBehaviour{
        @Override
        public void action() {
            ACLMessage message = receive(agreeTemplate);
            while(message != null){
                String[] tokens = message.getContent().split(",");
                int x = Integer.parseInt(tokens[0]);
                int y = Integer.parseInt(tokens[1]);
                cleanedCells.add(new Position(x, y));
                message = receive(agreeTemplate);
            }
        }
    }

    private class CleaningBehaviour extends CyclicBehaviour{
        public void broadcastPosition(){
            for(int i=0;i<nrAgents;i++){
                if(i!=id){
                    ACLMessage message = new ACLMessage(ACLMessage.AGREE);
                    message.addReceiver(new AID("a" + i, AID.ISLOCALNAME));
                    message.setContent(position.toString());
                    send(message);
                }
            }
        }

        @Override
        public void action() {
            ACLMessage message = new ACLMessage(ACLMessage.REQUEST);
            message.addReceiver(new AID("env", AID.ISLOCALNAME));
            message.setContent(id + "," + position);
            send(message);

            ACLMessage isDirtyMessage = receive(requestTemplate);
            while (!(isDirtyMessage != null && isDirtyMessage.getPerformative() == ACLMessage.REQUEST)) {
                sleep(10);
                isDirtyMessage = receive(requestTemplate);
            }
            boolean isDirty = Boolean.parseBoolean(isDirtyMessage.getContent());
            if(!isDirty) {
                broadcastPosition();
                cleanedCells.add(position);
                return;
            }
            sleep(3000); // cleaning

            message = new ACLMessage(ACLMessage.CONFIRM);
            message.addReceiver(new AID("env", AID.ISLOCALNAME));
            message.setContent(id + "," + position);
            send(message);

            ACLMessage okMessage = receive(confirmTemplate);
            while (!(okMessage != null && okMessage.getPerformative() == ACLMessage.CONFIRM)) {
                sleep(10);
                okMessage = receive(confirmTemplate);
            }
            broadcastPosition();
            cleanedCells.add(position);
        }
    }

    private class CommunicateInitialPosition extends OneShotBehaviour{
        @Override
        public void action() {
            System.out.println(id + ": sending initial position " + position);
            ACLMessage message = new ACLMessage(ACLMessage.INFORM);
            message.addReceiver(new AID("env", AID.ISLOCALNAME));
            message.setContent(id + "," + position);
            send(message);
            sleep(2000);
        }
    }


    private class MovementBehaviour extends CyclicBehaviour {
        private List<Position> getNextPositions(){
            List<Position> positions = new ArrayList<>();
            for(int i=-1;i<=1;i++)
                for(int j=-1;j<=1;j++)
                    if(!(i==0 && j==0)){
                        int new_x = position.x+i;
                        int new_y = position.y+j;
                        if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols) {
                            positions.add(new Position(new_x, new_y));
                        }
                    }
            return positions;
        }

        private List<Position> filterNextPositions(List<Position> positions){
            List<Position> filtered = new LinkedList<>();
            for(Position position: positions)
                if(!cleanedCells.contains(position))
                    filtered.add(position);

            if(filtered.isEmpty() && !previousPositions.isEmpty())
                filtered.add(previousPositions.peek());
            return filtered;
        }

        public void action() {
            List<Position> nextPositions = filterNextPositions(getNextPositions());
            Collections.shuffle(nextPositions);
            for(Position newPosition:nextPositions){
                ACLMessage message = new ACLMessage(ACLMessage.INFORM);
                message.addReceiver(new AID("env", AID.ISLOCALNAME));
                message.setContent(id + "," + position + "," + newPosition);
                send(message);

                ACLMessage okMessage = receive(informTemplate);
                while (!(okMessage != null && okMessage.getPerformative() == ACLMessage.INFORM)) {
                    sleep(10);
                    okMessage = receive(informTemplate);
                }

                if(okMessage.getContent().equals("1")){
                    if(!previousPositions.isEmpty() && previousPositions.peek().equals(newPosition))
                        previousPositions.pop();
                    else
                        previousPositions.push(position);
                    cleanedCells.add(position);
                    position = newPosition;

                    break;
                }
            }
            sleep(new Random().nextInt(500) + 1000);
        }
    }
}
