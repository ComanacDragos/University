package simplevacuumagent;

import agent.Action;
import agent.Agent;
import agent.Percept;
import simplevacuumagent.VacuumPercept;

/** The Vacuum Cleaning Agent - it is a simple reactive agent*/
public class VacuumAgent extends Agent {

	/** a deliberative agent stores its internal state - it may keep a history in the environment*/

	private boolean dirt;
	private boolean wall;

	public void see(Percept p) {
		if (((VacuumPercept) p).seeDirt())
			dirt = true;
		else
			dirt = false;
		if (((VacuumPercept) p).seeWall())
			wall = true;
		else
			wall = false;
	}

	public Action selectAction() {
		/** The agent action selection function */
		if (dirt) {
			return new SuckDirt();
		}
		if (wall)
			return new TurnRight();
		/** The agent has no strategy, it selects randomly an action */
		int r = (int) Math.floor(Math.random() * 2);
		switch (r) {
		case 0:
			return new GoForward();
		case 1:
			return new TurnRight();
		}
		return null;
	}
}