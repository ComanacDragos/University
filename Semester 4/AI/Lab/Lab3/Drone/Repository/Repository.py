from Drone.Domain.Map import *
from Drone.Domain.settings import *
from Drone.Domain.Drone import *
import pickle


class Repository:
    def __init__(self, mapFile=None):
        self._map = Map()
        if mapFile is not None:
            self.loadMap(mapFile)
        else:
            self._map.randomMap()

        self._population = []

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