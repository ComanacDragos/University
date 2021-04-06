from Domain.Ant import *


class MapGraph:
    def __init__(self, mapRepo):
        self._map = mapRepo
        self._trace = {}

    def trace(self, source, destination):
        if (source, destination) not in self._trace:
            self._trace[(source, destination)] = Q
            self._trace[(destination, source)] = Q
        return self._trace[(source, destination)]

    def setTrace(self, source, destination, value):
        self._trace[(source, destination)] = value

    def cost(self, source, destination, endPoint):
        if not self._map.validPosition(destination):
            return 99999
        return 1 # Ant.euclideanDistance(destination, endPoint) + 1

    def nextNodes(self, node):
        x, y = node
        possibleNeighbors = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]
        return [position for position in possibleNeighbors if self._map.validPosition(position)]

    def decay(self):
        for item in self._trace:
            self._trace[item] *= (1-DECAY)



