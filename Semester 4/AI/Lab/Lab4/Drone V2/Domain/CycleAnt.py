from Domain.Ant import Ant
from Domain.settings import *


class CycleAnt(Ant):
    @property
    def fitness(self):
        return sum([self._graph.cost(self.representation[i], self.representation[i+1])
                    for i in range(len(self.representation)-1)])

    def endCond(self):
        return len(self.representation) == len(self._graph.nodes)

    def computeProduct(self, node):
        if node == self._path[-1]:
            return 0

        return (self._graph.trace(self._path[-1], node) ** ALPHA) * \
               (1 / self._graph.cost(self._path[-1], node) ** BETA)
