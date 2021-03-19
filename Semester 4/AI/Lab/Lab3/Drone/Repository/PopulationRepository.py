from Drone.Domain.Individual import *
from numpy import average


class PopulationRepository:
    def __init__(self, populationSize=POPULATION_SIZE, individualSize=INDIVIDUAL_SIZE):
        self._population = [Individual(individualSize) for _ in range(populationSize)]

    def evaluate(self, fitnessFunction):
        for x in self._population:
            x.fitness = fitnessFunction(x.representation)

    def selection(self, k=0):
        indexes = set()
        while len(indexes) != k:
            indexes.add(randint(0, len(self._population) - 1))
        return [(i, self._population[i]) for i in indexes]

    def bestChromosome(self):
        return min(self._population, key=lambda c: c.fitness)

    @property
    def fitnessAverage(self):
        return average([individual.fitness for individual in self._population])

    def setPopulation(self, newPopulation):
        self._population = newPopulation

    def __getitem__(self, item):
        return self._population[item]

    def __setitem__(self, key, value):
        self._population[key] = value

    def __len__(self):
        return len(self._population)
