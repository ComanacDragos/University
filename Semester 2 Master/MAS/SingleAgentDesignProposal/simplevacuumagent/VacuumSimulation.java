package simplevacuumagent;

import agent.*;

/** A simulator for the vacuum cleaning world environment. */
public class VacuumSimulation extends Simulation {

	public VacuumSimulation(VacuumEnvironment env, VacuumAgent a) {
		super(env, a);
	}

	/** The simulation is complete when the robot has cleaned all the dirt */
	protected boolean isComplete() {
		if (((VacuumState) (env.currentState())).getNumDirtyLocs() == 0)
			return true;
		else
			return false;
	}

	/**
	 * Starts the program.
	 */
	public static void main(String[] args) {

		System.out.println("The Vacuum Cleaner World Agent Test");
		System.out.println("-----------------------------------");
		System.out.println();

		VacuumAgent a = new VacuumAgent();
		VacuumEnvironment env = new VacuumEnvironment();
		VacuumSimulation sim = new VacuumSimulation(env, a);
		VacuumState initState = VacuumState.getInitState();

		/** starts simulation */
		sim.start(initState);
	}

}
