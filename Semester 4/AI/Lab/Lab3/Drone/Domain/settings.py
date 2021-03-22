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

KEEP_PROBABILITY = 0.5
EARLY_STOP = 100

INDIVIDUAL_SIZE = 100  # steps until the battery depletes
POPULATION_SIZE = 10000 # 5000
GENERATIONS = 3000

MUTATE_PROB = 0.3
CROSSOVER_PROB = 0.9
ERROR_FACTOR = 0.3  # 0.2 # 0.5

#FITNESS_FUNCTION = "simpleFitness"
#FITNESS_FUNCTION = "uniquePositionsFitness"
#FITNESS_FUNCTION = "variationFitness"
#FITNESS_FUNCTION = "neighborsFitness"
FITNESS_FUNCTION = "circularFitness"

#ITERATION_STRATEGY = "generational"
ITERATION_STRATEGY = "steadyState"
STEADY_STATE_NO_OFFSPRINGS = 800

TARGET = "cpu"

NEIGHBORS_RADIUS = 2
GENE_STRENGTH = 10

#OUTPUT_FILE = "Resources/Paths/testCircular.path"
OUTPUT_FILE = "Resources/Paths/uniquePositions.path"
