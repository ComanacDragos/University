package simplevacuumagent;

/** A utility class that encapsulates information about compass directions. */
public class Direction {

  public static final int NORTH = 0;
  public static final int EAST = 1;
  public static final int SOUTH = 2;
  public static final int WEST = 3;

  /** An array for determining the change in X position that would
      correspond to a step in the direction indexed. */
  public static final int[] DELTA_X = new int[4];

  /** An array for determining the change in Y position that would
      correspond to a step in the direction indexed. */
  public static final int[] DELTA_Y = new int[4];

  /* static initializer for the DELTA_X and DELTA_Y arrays. */
  static {
    DELTA_X[NORTH] = 0;
    DELTA_X[EAST] = 1;
    DELTA_X[SOUTH] = 0;
    DELTA_X[WEST] = -1;

    DELTA_Y[NORTH] = -1;
    DELTA_Y[EAST] = 0;
    DELTA_Y[SOUTH] = 1;
    DELTA_Y[WEST] = 0;
  }

  public static String toString(int direction) {
    switch(direction) {
      case NORTH:
        return "NORTH";
      case EAST:
        return "EAST";
      case SOUTH:
        return "SOUTH";
      case WEST:
        return "WEST";
      default:
        return "INVALID";
    }
  }
}
