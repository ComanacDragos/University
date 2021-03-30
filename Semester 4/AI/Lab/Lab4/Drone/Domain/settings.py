# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
YELLOW = (255, 255, 0)
PURPLE = (255, 0, 255)
BRIGHT_BLUE = (0, 255, 255)
# define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3

DIRECTIONS = [(-1, 0), (1, 0), (0, 1), (0, -1)]

WIDTH = 40
HEIGHT = 40

SQUARE_WIDTH = 20
SQUARE_HEIGHT = 20

WALL = 1
EMPTY = 0

FILL_FACTOR = 0.2

ANT_SIZE = 100  # steps until the battery depletes
NO_ANTS = 3
EPOCHS = 300

ALPHA = 2.5
BETA = 0.8 # 1.3
DECAY = 0.01
Q0 = 0.5
Q = 100.0

SENSORS = 5

SEED = 5

ERROR_FACTOR = 10000

FITNESS_FUNCTION = "simpleFitness"

NEIGHBORS_RADIUS = 2
GENE_STRENGTH = 10

OUTPUT_FILE = "Output/output.txt"
