package agent;

/**
 * An abstract software agent class. The agent must be managed by the Simulation
 * class
 */
public abstract class Agent {

	/**
	 * Provides a Percept to the agent. If the agent has internal state, this
	 * method should update it.
	 */
	public abstract void see(Percept p);

	/**
	 * Have the agent select its next action to perform. In an agent with
	 * internal state, this implements the action: I -> A function.
	 */
	public abstract Action selectAction();

}
