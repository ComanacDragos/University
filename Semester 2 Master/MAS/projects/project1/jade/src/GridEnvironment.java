import jade.core.AID;
import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;
import jade.lang.acl.MessageTemplate;

import java.awt.event.WindowEvent;
import java.util.HashMap;
import java.util.Map;

public class GridEnvironment extends Agent {
    private GridGUI gui;
    int nrAgents, nrDirty=0;
    Cell[][] grid;

    Map<Integer, Integer> scores = new HashMap<>();

    protected void setup() {
        Object[] args = getArguments();
        int rows, cols, dirtyPercent;
        if (args != null && args.length > 0) {
            rows = Integer.parseInt((String) args[0]);
            cols = Integer.parseInt((String) args[1]);
            dirtyPercent = Integer.parseInt((String) args[2]);
            nrAgents = Integer.parseInt((String) args[3]);
        }else{
            throw new RuntimeException("Environment did not receive arguments");
        }
        gui = new GridGUI(rows, cols);

        grid = new Cell[rows][cols];
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++){
                boolean dirty = Math.random() * 100 < dirtyPercent;
                grid[i][j] = new Cell(dirty, -1);
                if(dirty)
                    nrDirty += 1;
            }

        addBehaviour(new AgentExitBehaviour());
        addBehaviour(new LocationUpdateBehaviour());
    }

    private class AgentExitBehaviour extends CyclicBehaviour {
        int doneAgents = 0;

        MessageTemplate template = MessageTemplate.MatchPerformative(ACLMessage.CANCEL);

        public void action(){
            ACLMessage message = receive(template);
            if (message != null) {
                String[] tokens = message.getContent().split(",");
                int id = Integer.parseInt(tokens[0]);
                int x = Integer.parseInt(tokens[1]);
                int y = Integer.parseInt(tokens[2]);

                Cell cell = grid[y][x];
                if(cell.agentId != id || cell.isDirty)
                    throw new RuntimeException("Bad exit call");
                cell.agentId = -1;
                doneAgents += 1;
                gui.updateGrid(grid);
                if(doneAgents == nrAgents) {
                    System.out.println("Exit env...");
                    doDelete();
                    gui.dispatchEvent(new WindowEvent(gui, WindowEvent.WINDOW_CLOSING));
                    Runtime.getRuntime().exit(0);
                }
            }
        }
    }

    private class LocationUpdateBehaviour extends CyclicBehaviour {
        int receivedInitialPositions = 0;
        MessageTemplate template = MessageTemplate.or(
                MessageTemplate.MatchPerformative(ACLMessage.INFORM),
                MessageTemplate.or(
                        MessageTemplate.MatchPerformative(ACLMessage.REQUEST),
                        MessageTemplate.MatchPerformative(ACLMessage.CONFIRM)
                )
        );

        public void action(){
            ACLMessage message = receive(template);
            if (message != null) {
                switch (message.getPerformative()){
                    case ACLMessage.INFORM -> movementHandler(message);
                    case ACLMessage.REQUEST -> checkIfDirty(message);
                    case ACLMessage.CONFIRM -> cleanDirt(message);
                }
            } else {
                block();
            }
        }

        public void checkIfDirty(ACLMessage message){
            String[] tokens = message.getContent().split(",");
            int id = Integer.parseInt(tokens[0]);
            int x = Integer.parseInt(tokens[1]);
            int y = Integer.parseInt(tokens[2]);

            Cell cell = grid[y][x];
            if(cell.agentId != id)
                throw new RuntimeException("Agent requested something on a bad cell " + id);

            ACLMessage isDirtyMessage = new ACLMessage(ACLMessage.REQUEST);
            isDirtyMessage.addReceiver(new AID(message.getSender().getLocalName(), AID.ISLOCALNAME));
            isDirtyMessage.setContent(String.valueOf(cell.isDirty));
            send(isDirtyMessage);
        }

        public void cleanDirt(ACLMessage message){
            String[] tokens = message.getContent().split(",");
            int id = Integer.parseInt(tokens[0]);
            int x = Integer.parseInt(tokens[1]);
            int y = Integer.parseInt(tokens[2]);

            Cell cell = grid[y][x];
            if(cell.agentId != id || !cell.isDirty)
                throw new RuntimeException("Agent requested bad cleaning " + id);
            cell.isDirty = false;

            scores.put(id, scores.get(id) + 1);

            int cleaned = scores.entrySet().stream().map(
                    Map.Entry::getValue
            ).reduce(0, Integer::sum);

            System.out.println("\nSCORE " + cleaned + "/" + nrDirty);
            for(Map.Entry<Integer, Integer> entry : scores.entrySet()) {
                System.out.println(entry.getKey() + " -> " + entry.getValue());
            }
            System.out.println("\n");

            ACLMessage okMessage = new ACLMessage(ACLMessage.CONFIRM);
            okMessage.addReceiver(new AID(message.getSender().getLocalName(), AID.ISLOCALNAME));
            send(okMessage);
            gui.updateGrid(grid);
        }

        public void movementHandler(ACLMessage message) {
            String[] tokens = message.getContent().split(",");
            boolean gridUpdate = false;
            if(tokens.length == 3){
                // initial position
                int id = Integer.parseInt(tokens[0]);
                int x = Integer.parseInt(tokens[1]);
                int y = Integer.parseInt(tokens[2]);
                grid[y][x].agentId = id;
                grid[y][x].visited = true;
                receivedInitialPositions ++;
                gridUpdate = true;
                scores.put(id, 0);
            }else{
                int id = Integer.parseInt(tokens[0]);
                int old_x = Integer.parseInt(tokens[1]);
                int old_y = Integer.parseInt(tokens[2]);
                int x = Integer.parseInt(tokens[3]);
                int y = Integer.parseInt(tokens[4]);

                ACLMessage okMessage = new ACLMessage(ACLMessage.INFORM);
                okMessage.addReceiver(new AID(message.getSender().getLocalName(), AID.ISLOCALNAME));
                if(grid[y][x].agentId != -1 || receivedInitialPositions != nrAgents){
                    okMessage.setContent(String.valueOf(0));
                }else{
                    grid[old_y][old_x].agentId = -1;
                    grid[old_y][old_x].visited = true;
                    grid[y][x].agentId = id;
                    grid[y][x].visited = true;
                    okMessage.setContent(String.valueOf(1));
                    gridUpdate = true;
                }
                send(okMessage);
            }
            if(gridUpdate)
                gui.updateGrid(grid);

        }

    }

}
