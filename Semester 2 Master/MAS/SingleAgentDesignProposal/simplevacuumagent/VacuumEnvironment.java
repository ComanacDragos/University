package simplevacuumagent;

import agent.*;

import simplevacuumagent.VacuumPercept;

/** A simulator for the vacuum cleaning world environment. */
public class VacuumEnvironment extends Environment{

  public VacuumEnvironment() {
  }
    
  /** Creates a percept for an agent. This implements the see: S -> P
      function. */
  protected Percept getPercept(Agent a) {
    
    VacuumPercept p;

    if (state instanceof VacuumState) {
      p = new VacuumPercept((VacuumState)state, a);
      System.out.println("Percept: " + p.toString());
      return p;
    }
    else {
      System.out.println("ERROR - state is not a VacuumState object.");
      return null;
    }
  }

  
  /** Executes an agent's action and update the environment's state. */
  protected void updateState(Agent a, Action action) {

    super.updateState(a, action);
    System.out.println("Action: " + action.toString());
    System.out.println();
  }

 
 }
