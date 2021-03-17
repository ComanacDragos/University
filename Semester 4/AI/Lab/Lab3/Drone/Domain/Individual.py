from Drone.Domain.Gene import *
from Drone.Domain.settings import *
from random import random
from random import randint


class Individual:
    def __init__(self, size=INDIVIDUAL_SIZE):
        self._size = size
        self._representation = [Gene() for _ in range(size)]
        self._fitness = None

    @property
    def fitness(self):
        return self._fitness

    @fitness.setter
    def fitness(self, newFitness):
        self._fitness = newFitness

    def mutate(self, mutateProbability=MUTATE_PROB):
        if random() < mutateProbability:
            pass
            # perform a mutation with respect to the representation

    def crossover(self, otherParent, crossoverProbability=CROSSOVER_PROB):
        firstOffspring, secondOffspring = Individual(self._size), Individual(self._size)
        if random() < crossoverProbability:
            pass
            # perform the crossover between the self and the otherParent

        return firstOffspring, secondOffspring
