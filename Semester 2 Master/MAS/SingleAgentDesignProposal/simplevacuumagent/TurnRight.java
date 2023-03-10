package simplevacuumagent;

import agent.Action;
import agent.Agent;
import agent.State;

/**
 * A vacuum cleaning world action that causes the agent to turn 90 degrees to
 * the right.
 */
public class TurnRight extends Action {

	public TurnRight() {

	}

	/**
	 * Returns the state that results from the agent turning right in the given
	 * state. In order to avoid creating unnecessary objects, we do not create a
	 * new state, but instead modify the old one. This would have to changed if
	 * the Environment needs to maintain a history of states.
	 */
	public State execute(Agent a, State s) {

		int dir;
		int newDir;
		VacuumState state = null;

		if (s instanceof VacuumState)
			state = (VacuumState) s;
		else
			System.out
					.println("ERROR - Argument to TurnRight.execute() is not of type VacuumState");

		dir = state.getAgentDir();

		newDir = dir + 1;
		if (newDir > 3)
			newDir = 0;
		state.setAgentDir(newDir);

		return state;
	}

	public String toString() {
		return "TURN RIGHT";
	}
}
