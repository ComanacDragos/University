from Drone.Domain.Map import *
from Drone.Domain.settings import *
from Drone.Domain.Drone import *
from Drone.Domain.Individual import *
import pickle


class Repository:
    def __init__(self, mapFile=None, populationSize=POPULATION_SIZE, individualSize=INDIVIDUAL_SIZE):
        self._map = Map()
        if mapFile is not None:
            self.loadMap(mapFile)
        else:
            self._map.randomMap()

        self._population = [Individual(individualSize) for _ in range(populationSize)]

    def evaluate(self, fitnessFunction):
        for x in self._population:
            x.fitness = fitnessFunction(x.representation)

    def selection(self, k=0):
        indexes = set()
        while len(indexes) != k:
            indexes.add(randint(0, len(self._population) - 1))
        return [self._population[i] for i in indexes]

    def saveMap(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self._map, f)
            f.close()

    def loadMap(self, numFile):
        with open(numFile, "rb") as f:
            self._map = pickle.load(f)
            f.close()

    @property
    def mapImage(self):
        return self._map.image()

    def __getitem__(self, item):
        if type(item) is int:
            return self._population[item]
        return self._map[item]
