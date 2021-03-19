from Drone.Domain.Gene import *
from Drone.Domain.settings import *
from random import random
from random import randint


class Individual:
    def __init__(self, size=INDIVIDUAL_SIZE, representation=None):
        if representation is None:
            self._representation = [Gene().value for _ in range(size)]
        else:
            self._representation = representation
            if size != len(representation):
                raise Exception("Bad representation")

        self._fitness = None

    def mutate(self, mutateProbability=MUTATE_PROB):
        if random() < mutateProbability:
            self._representation[randint(0, len(self._representation) - 1)] = Gene().value

    def crossoverTwo2Two(self, otherParent, crossoverProbability=CROSSOVER_PROB):
        firstOffspring, secondOffspring = Individual(len(self._representation)), Individual(len(self._representation))
        if random() < crossoverProbability:
            splitIndex = randint(1, len(self._representation) - 2)
            firstOffspring._representation = self.representation[:splitIndex] + otherParent.representation[splitIndex:]
            secondOffspring._representation = otherParent.representation[:splitIndex] + self.representation[splitIndex:]

            return firstOffspring, secondOffspring
        return self, otherParent

    def crossover(self, otherParent, crossoverProbability=CROSSOVER_PROB):
        if random() < crossoverProbability:
            splitIndex = randint(1, len(self._representation) - 2)
            newRepresentation = self.representation[:splitIndex] + otherParent.representation[splitIndex:]

            return Individual(len(self._representation), newRepresentation)
        return self

    @property
    def fitness(self):
        return self._fitness

    @fitness.setter
    def fitness(self, newFitness):
        self._fitness = newFitness

    @property
    def representation(self):
        return self._representation
