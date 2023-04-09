import jade.core.Agent;
import jade.core.behaviours.CyclicBehaviour;
import jade.lang.acl.ACLMessage;

public class GridEnvironment extends Agent {
    private int dirtyPercent;
    private GridGUI gui;

    protected void setup() {
        Object[] args = getArguments();
        int rows, cols;
        if (args != null && args.length > 0) {
            rows = Integer.parseInt((String) args[0]);
            cols = Integer.parseInt((String) args[1]);
            dirtyPercent = Integer.parseInt((String) args[2]);
        }else{
            throw new RuntimeException("Environment did not receive arguments");
        }
        gui = new GridGUI(rows, cols);

        addBehaviour(new LocationUpdateBehavior());
    }

    private class LocationUpdateBehavior extends CyclicBehaviour {
        public void action() {
            ACLMessage message = receive();
            if (message != null && message.getPerformative() == ACLMessage.INFORM) {
                String[] location = message.getContent().split(",");
                int x = Integer.parseInt(location[0]);
                int y = Integer.parseInt(location[1]);
                gui.updateGrid(x, y, 0);
            } else {
                block();
            }
        }

    }

}
