package simplevacuumagent;

import agent.*;

/** A percept in the vacuum cleaning world. */
public class VacuumPercept extends Percept {

	protected boolean dirt;
	protected boolean wall;

	/**
	 * Constructs a vacuum world percept. If the agent is in a square that has
	 * dirt, then creates a percept that sees dirt.
	 */
	public VacuumPercept(VacuumState state, Agent agent) {

		super(state, agent);

		int x, y;

		x = state.getAgentX();
		y = state.getAgentY();
		int dir = state.getAgentDir();

		/** determine dirt */
		if (state.hasDirt(x, y))
			dirt = true;
		else
			dirt = false;

		// determine wall
		int viewX = x + Direction.DELTA_X[dir];
		int viewY = y + Direction.DELTA_Y[dir];
		if (state.isWall(viewX, viewY))
			wall = true;
		else
			wall = false;

	}

	/** Returns true if the percept reflects that the agent is over dirt. */
	public boolean seeDirt() {

		return dirt;
	}

	/**
	 * Returns true if the percept reflects that the square immediately in front
	 * of the agent contains an obstacle.
	 */
	public boolean seeWall() {

		return wall;
	}

	public String toString() {

		StringBuffer pstring;

		pstring = new StringBuffer(5);
		if (dirt == true)
			pstring.append("DIRT ");
		else if (wall == true)
			pstring.append("WALL ");
		else
			pstring.append("CLEAR ");
		return pstring.toString();
	}
}
