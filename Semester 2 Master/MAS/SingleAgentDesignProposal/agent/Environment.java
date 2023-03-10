package agent;


/** This can be used for either single or multi-agent environments. */
public abstract class Environment {

  protected State state;

  /** Constructs a new environment */
  public Environment() {

  }

  /** Creates a percept for an agent. This should implement the
      see: S -> P function. */
  protected abstract Percept getPercept(Agent a);

  /** Executes an agent's action and update the environment's state. This
   implements the env: S x A -> S function. */
  protected void updateState(Agent a, Action action) {

    state = action.execute(a, state);
  }
  
  /** The current state of the environment. */
  public State currentState(){
	  return state;
  }

  /** Set the initial state of the environment. */
  public void setInitialState(State s){
	  state=s;
  }
  
  
}



