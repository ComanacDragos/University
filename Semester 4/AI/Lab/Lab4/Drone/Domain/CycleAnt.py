from Domain.Ant import Ant
from Domain.settings import *
from random import randint


class CycleAnt(Ant):
    def __init__(self, startingPoint, endPoint, graph):
        super().__init__(startingPoint, endPoint, graph)
        self._sensorEnergy = {sensor: 0 for sensor in graph.sensorStrengths}
        self._cost = 1
        self._sensorCost = 0
        self._remainingEnergy = ANT_SIZE

    @property
    def sensorEnergy(self):
        return self._sensorEnergy

    def addMove(self):
        if super().addMove():
            self._cost += (self._graph.cost(self.representation[-2], self.representation[-1]) - 1)
            if self.endCond():
                self._remainingEnergy = ANT_SIZE - self._cost
                if self._remainingEnergy > 0:
                    for sensor in self._graph.sensorStrengths:
                        sensorCost = randint(1, min(self._remainingEnergy, self._graph.sensorStrengths[sensor]))
                        self._sensorEnergy[sensor] = sensorCost
                        self._remainingEnergy -= sensorCost
                        if self._remainingEnergy == 0:
                            break
                self._sensorCost = sum(self._sensorEnergy.values())
            return True
        return False

    @property
    def fitness(self):
        if self._sensorCost == 0:
            if self._remainingEnergy == 0:
                return self._cost
            return self._cost + 1
        return self._cost + 1/(100*self._sensorCost)

    def endCond(self):
        return len(self.representation) == len(self._graph.nodes)

    def computeProduct(self, node):
        if node == self._path[-1]:
            return 0

        return (self._graph.trace(self._path[-1], node) ** ALPHA) * \
               (1 / self._graph.cost(self._path[-1], node) ** BETA)
