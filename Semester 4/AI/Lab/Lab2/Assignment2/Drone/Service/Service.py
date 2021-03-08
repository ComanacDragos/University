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
        # self._map.randomMap()

        position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)
        while self._map[position] != 0:
            position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)

        self._drone = Drone(position)
        self.printFlag = True

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
        drone = pygame.image.load("Resources/drona.png")
        image = self._map.image()
        image.blit(drone, (self._drone.position[1] * SQUARE_HEIGHT, self._drone.position[0] * SQUARE_WIDTH))
        return image

    def mapWithPath(self, finalPosition):
        markCommon = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
        markAStar = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
        markGreedy = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))

        markCommon.fill(GREEN)
        markAStar.fill(YELLOW)
        markGreedy.fill(RED)

        image = self._map.image()
        aStarPath = self.path(finalPosition, self.searchAStar)
        greedyPath = self.path(finalPosition, self.searchGreedy)

        for move in aStarPath:
            if move in greedyPath:
                mark = markCommon
            else:
                mark = markAStar
            image.blit(mark, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))

        for move in [position for position in greedyPath if position not in aStarPath]:
            image.blit(markGreedy, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))

        drone = pygame.image.load("Resources/drona.png")
        image.blit(drone, (self._drone.position[1] * SQUARE_HEIGHT, self._drone.position[0] * SQUARE_WIDTH))
        return image

    def path(self, finalPosition, strategy):
        if self._map[finalPosition] == WALL:
            return []
        return strategy(self._drone.position, finalPosition)

    def bestFirstSearch(self, initialPos, finalPos, costFunction):
        found = False
        visited = set()
        toVisit = PriorityQueue()
        toVisit.put((0, initialPos))
        predecessors = {initialPos: -1}

        while not toVisit.empty() and not found:
            if toVisit.empty():
                return False  # ??
            _, node = toVisit.get_nowait()

            if node in visited:
                continue
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
        return self.process_predecessors(
            self.bestFirstSearch(initialPos, finalPos,
                                 lambda position: self.euclidean_distance(initialPos, position) +
                                                  self.euclidean_distance(position, finalPos)),
            finalPos
        )

    def searchGreedy(self, initialPos, finalPos):
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
        return [(x, y) for x, y in [(x, y - 1), (x + 1, y), (x, y + 1), (x - 1, y)]
                if 0 <= x < HEIGHT and 0 <= y < WIDTH]

    @staticmethod
    def process_predecessors(predecessors, destination):
        if destination not in predecessors:
            return []
        current_node = destination
        path = []
        while current_node != -1:
            path.insert(0, current_node)
            current_node = predecessors[current_node]
        return path

    @staticmethod
    def euclidean_distance(leftPos, rightPos):
        return np.linalg.norm(np.array(leftPos) - np.array(rightPos))
