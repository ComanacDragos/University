from Drone.Domain.Drone import *
from Drone.Domain.Map import *
from queue import PriorityQueue
from random import randint
import pickle
import numpy as np


class Service:
    def __init__(self):
        self._map = Map()
        self.loadMap("Resources/test1.map")

        position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)
        while self._map[position] != 0:
            position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)

        self._drone = Drone(position)

    def saveMap(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self._map, f)
            f.close()

    def loadMap(self, numFile):
        with open(numFile, "rb") as f:
            self._map = pickle.load(f)
            f.close()

    def mapImage(self):
        return self._map.image()

    def mapWithDrone(self):
        drona = pygame.image.load("Resources/drona.png")
        image = self._map.image()
        image.blit(drona, (self._drone.position[1] * SQUARE_HEIGHT, self._drone.position[0] * SQUARE_WIDTH))

        return image

    def mapWithPath(self):
        mark = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
        mark.fill(GREEN)
        image = self._map.image()
        for move in self.path():
            image.blit(mark, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))
        return image

    def path(self):
        return self.searchGreedy((5, 7), (6, 12))

    def bestFirstSearch(self, initialPos, finalPos, costFunction):
        found = False
        visited = set()
        toVisit = PriorityQueue()
        toVisit.put((0, initialPos))
        predecessors = {initialPos: -1}

        while not toVisit.empty() and not found:
            if toVisit.empty():
                return False  # ??
            _, node = toVisit.get()
            visited.add(node)

            if node == finalPos:
                found = True
            else:
                for child in [position for position in self.neighbors(node)
                              if position not in visited and self._map[position] != WALL]:
                    toVisit.put((costFunction(child), child))
                    predecessors[child] = node
        return predecessors

    def searchAStar(self, initialPos, finalPos):
        # TO DO
        # implement the search function and put it in controller
        # returns a list of moves as a list of pairs [x,y]

        pass

    def searchGreedy(self, initialPos, finalPos):
        # TO DO
        # implement the search function and put it in controller
        # returns a list of moves as a list of pairs [x,y]
        return self.process_predecessors(
            self.bestFirstSearch(initialPos, finalPos,
                                 lambda position: self.euclidean_distance(position, finalPos)),
            finalPos
        )

    def dummysearch(self, initialPos, finalPos):
        # example of some path in test1.map from [5,7] to [7,11]
        return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [6, 12]]

    @staticmethod
    def neighbors(position):
        x, y = position
        return [(x, y - 1), (x + 1, y), (x, y + 1), (x - 1, y)]

    @staticmethod
    def process_predecessors(predecessors, destination):
        current_node = destination
        path = []
        while current_node != -1:
            path.insert(0, current_node)
            current_node = predecessors[current_node]
        return path

    @staticmethod
    def euclidean_distance(leftPos, rightPos):
        return np.linalg.norm(np.array(leftPos) - np.array(rightPos))
