package agent;

/**
 * The top-level class for an agent simulation. This can be used for either
 * single or multi-agent simulations.
 */
public abstract class Simulation {

	protected Agent agent = null;
	protected Environment env;

	/**
	 * Constructs a new simulation. Initializes the agent(or agents vector) and
	 * the environment.
	 */
	public Simulation(Environment e, Agent a) {

		agent = a;
		env = e;

	}

	/**
	 * Runs the simulation starting from a given state. This consists of a
	 * sense-act loop for the/(each) agent. An alternative approach would be to
	 * allow the agent to decide when it will sense and act.
	 */
	public void start(State initState) {
		env.setInitialState(initState);
		env.currentState().display();

		while (!isComplete()) {
			Percept p = env.getPercept(agent);
			agent.see(p);
			Action action = agent.selectAction();
			env.updateState(agent, action);
			//env.currentState().display();
		}
		System.out.println("END of simulation");
	}

	/** Is the simulation over? Returns true if it is, otherwise false. */
	protected abstract boolean isComplete();

}
