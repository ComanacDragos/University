package simplevacuumagent;

import agent.State;
import java.io.*;

/** Represents a state in the vacuum world. */
public class VacuumState extends State {

	/* Constants for the initial state of the agent. */
	protected static int INIT_X = 1;
	protected static int INIT_Y = 1;
	protected static int INIT_DIR = Direction.SOUTH;

	private static final int CLEAR = 0;
	private static final int DIRT = 1;
	private static final int WALL = 2;

	/*
	 * Default map for initial state. The room is completely surrounded by walls 
	 */
	protected static int[][] defaultMap = {
			{ WALL, WALL, WALL, WALL, WALL },
			{ WALL, CLEAR, CLEAR, CLEAR, WALL },
			{ WALL, CLEAR, DIRT,  CLEAR, WALL },
			{ WALL, CLEAR, CLEAR, DIRT, WALL },
			{ WALL, WALL, WALL, WALL, WALL } };

	protected static double DIRT_CHANCE = 0.3;

	/* Variables for the state of the agent. */
	protected int agentX;
	protected int agentY;
	protected int agentDir;

	/** An array that contains the locations of objects in the world. */
	protected int[][] map;

	protected int numDirtyLocs = 0;

	protected int height;
	protected int width;

	static final int DEFAULT_HEIGHT = 5;
	static final int DEFAULT_WIDTH = 5;

	/** Returns the default initial state for the vacuum world. */
	public static VacuumState getInitState() {

		VacuumState state;

		state = new VacuumState();
		state.width = defaultMap.length;
		state.height = defaultMap[0].length;
		state.map = new int[state.width][state.height];
		state.map = defaultMap;
		state.numDirtyLocs = 2;
		state.agentX = INIT_X;
		state.agentY = INIT_Y;
		state.agentDir = INIT_DIR;
		return state;
	}


	/** Constructs a new vacuum state. */
	public VacuumState() {
	}

	/** Returns the agent's X position. */
	public int getAgentX() {
		return agentX;
	}

	/** Returns the agent's Y position. */
	public int getAgentY() {
		return agentY;
	}

	/**
	 * Returns the agent's orientation. Note that the constants in the Direction
	 * class are used to interpret the meaning of this result.
	 */
	public int getAgentDir() {
		return agentDir;
	}

	/** Returns a string the represents the agent's orientation. */
	public String getAgentDirString() {
		return Direction.toString(agentDir);
	}

	/** Changes the agent's X position. */
	public void setAgentX(int x) {
		agentX = x;
	}

	/** Changes the agent's Y position. */
	public void setAgentY(int y) {
		agentY = y;
	}

	/** Changes the agent's orientation. */
	public void setAgentDir(int dir) {
		agentDir = dir;
	}

	/** Removes dirt from the specified location. */
	public void removeDirt(int x, int y) {

		if (map[x][y] == DIRT) {
			map[x][y] = CLEAR;
			numDirtyLocs--;
		}
	}

	/** Returns true if the specified location has dirt in it. */
	public boolean hasDirt(int x, int y) {

		if (map[x][y] == DIRT)
			return true;
		else
			return false;
	}

	/** Returns true if the specified location is a wall. */
	public boolean isWall(int x, int y) {

		if (map[x][y] == WALL)
			return true;
		else
			return false;
	}


	/** Returns true if the location is within bounds of the state's map. */
	public boolean inBounds(int x, int y) {

		if (x >= 0 && x < width && y >= 0 && y < height)
			return true;
		else
			return false;
	}

	/** Returns the number of dirty locations in the state. */
	public int getNumDirtyLocs() {

		return numDirtyLocs;
	}

	/**
	 * Prints an output of the state to the screen. This output includes a map as
	 * well as information about the agent's location and the direction it is
	 * facing. On the map, "A" denotes the agent and "*" denotes dirt.
	 */
	public void display() {

		for (int j = 1; j < width-1; j++)
			System.out.print("  " + j);
		System.out.println();

		System.out.print(" ");
		for (int j = 1; j < width-1; j++)
			System.out.print("+--");
		System.out.println("+");

		/*
		 * To print to the screen properly, the loop in the Y direction must be
		 * the outer loop.
		 */
		for (int i = 1; i < height-1; i++) {
			System.out.print(i + "|");
			for (int j = 1; j < width-1; j++) {
				if (i == agentY && j == agentX)
					System.out.print("A");
				else if (hasDirt(i, j))
					System.out.print("*");
				else
					System.out.print(" ");
				System.out.print(" |");
			}
			System.out.println();

			System.out.print(" +");
			for (int j = 1; j < width - 2; j++)
				System.out.print("--+");
			System.out.println("--+");

		}
		System.out.println("Location: (" + agentX + "," + agentY + ")  "
				+ "Facing: " + getAgentDirString());
		System.out.println();

		System.out.println("Press RETURN to continue.");

		BufferedReader console = new BufferedReader(new InputStreamReader(
				System.in));
		try {
			String input = console.readLine();
		} catch (IOException e) {
			System.out.println(e.getMessage());
			return;
		}

	}

}
