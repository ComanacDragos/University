from Domain.settings import *
from random import random
from random import choice
import numpy as np


class Ant:
    def __init__(self, startingPoint, endPoint, graph):
        self._path = [startingPoint]
        self._endPoint = endPoint
        self._graph = graph

    def computeProduct(self, node):
        if node == self._path[-1]:
            return 0
        return (self._graph.trace(self._path[-1], node) ** ALPHA) * \
               (1 / self._graph.cost(self._path[-1], node, self._endPoint) ** BETA)

    def endCond(self):
        return self._path[-1] == self._endPoint or len(self._path) > ANT_SIZE

    def addMove(self):
        if self.endCond():
            return False
        neighbors = self._graph.nextNodes(self._path[-1])
        nextNodes = [node for node in neighbors if node not in self._path]

        if len(nextNodes) == 0:
            nextNodes = neighbors

        pairs = [(node, self.computeProduct(node)) for node in nextNodes]
        if random() < Q0:
            self._path.append(
                max(pairs, key=lambda pair: pair[1])[0]
            )
        else:
            s = sum([pair[1] for pair in pairs])

            if s == 0:
                self._path.append(choice(nextNodes))
                return True

            prob = [(node, val/s) for node, val in pairs]
            prob = [
                (
                    prob[i][0],
                    sum([prob[j][1] for j in range(i+1)])
                )
                for i in range(len(prob))]
            r = random()
            i = 0
            while r > prob[i][1]:
                i += 1
            self._path.append(prob[i][0])
        return True

    @property
    def representation(self):
        return self._path

    @property
    def fitness(self):
        return self.euclideanDistance(self._path[-1], self._endPoint) * 60 + len(self._path) * 40

    @staticmethod
    def euclideanDistance(leftPos, rightPos):
        return np.linalg.norm(np.array(leftPos) - np.array(rightPos))
