from Drone.Domain.Drone import *
from Drone.Domain.Map import *
from queue import PriorityQueue
from random import randint
from random import choice
import pickle
import numpy as np
import time


class Service:
    def __init__(self):
        self._map = Map()
        self.loadMap("Resources/test1.map")
        # self._map.randomMap()

        position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)
        while self._map[position] != 0:
            position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)

        self._drone = Drone(position)
        self.positions = (None, None)
        self._execution_times = {}

        self.showTabu = False
        self.showSimulatedAnnealing = False
        self.showGreedyAndAStar = False
        self.computeSimulatedAnnealing = False
        self.simulatedAnnealingPath = []

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
        drone = pygame.transform.scale(pygame.image.load("Resources/drona.png"), (SQUARE_HEIGHT, SQUARE_WIDTH))
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

        if self.showGreedyAndAStar:
            for move in aStarPath:
                if move in greedyPath:
                    mark = markCommon
                else:
                    mark = markAStar
                image.blit(mark, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))

            for move in [position for position in greedyPath if position not in aStarPath]:
                image.blit(markGreedy, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))

        if self.showTabu:
            markTabu = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
            markTabu.fill(PURPLE)
            for move in self.path(finalPosition, self.searchTabu):
                image.blit(markTabu, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))

        if self.showSimulatedAnnealing and self.computeSimulatedAnnealing:
            self.simulatedAnnealingPath = self.path(finalPosition, self.searchSimulatedAnnealing)
            self.computeSimulatedAnnealing = False

        if self.showSimulatedAnnealing:
            markSimulated = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
            markSimulated.fill(BRIGHT_BLUE)
            for index, move in enumerate(self.simulatedAnnealingPath, start=50):
                markSimulated.set_alpha(index)
                image.blit(markSimulated, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))

        drone = pygame.transform.scale(pygame.image.load("Resources/drona.png"), (SQUARE_HEIGHT, SQUARE_WIDTH))
        image.blit(drone, (self._drone.position[1] * SQUARE_HEIGHT, self._drone.position[0] * SQUARE_WIDTH))

        if (self._drone.position, finalPosition) != self.positions:
            self.positions = (self._drone.position, finalPosition)
            self.computeSimulatedAnnealing = True

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
        start = time.time()
        path = self.processPredecessors(
            self.bestFirstSearch(initialPos, finalPos,
                                 lambda position: self.euclideanDistance(initialPos, position) +
                                                  self.euclideanDistance(position, finalPos)),
            finalPos
        )
        self._execution_times["A*"] = (time.time() - start, len(path))
        return path

    def searchGreedy(self, initialPos, finalPos):
        start = time.time()
        path = self.processPredecessors(
            self.bestFirstSearch(initialPos, finalPos,
                                 lambda position: self.euclideanDistance(position, finalPos)),
            finalPos
        )
        self._execution_times["Greedy"] = (time.time() - start, len(path))
        return path

    def dummysearch(self, initialPos, finalPos):
        # example of some path in test1.map from [5,7] to [7,11]
        return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [6, 12]]

    def searchTabu(self, initialPos, finalPos):
        currentPosition = initialPos
        path = []
        visited = set()
        visited.add(initialPos)

        start = time.time()
        while currentPosition != finalPos:
            next_positions = [position for position in self.neighbors(currentPosition)
                              if position not in visited and self._map[position] != WALL]

            if len(next_positions) == 0:
                if path:
                    currentPosition = path.pop()
                else:
                    path = []
                    break
                continue

            cost = lambda position: self.euclideanDistance(position, finalPos)
            candidate_position = min(next_positions, key=cost)
            if cost(candidate_position) < cost(currentPosition) or len(next_positions) == 1:
                path.append(currentPosition)
                currentPosition = candidate_position
            visited.add(candidate_position)

        if path:
            path.append(finalPos)
        self.executionTimes["Tabu"] = (time.time() - start, len(path))
        return path

    def searchSimulatedAnnealing(self, initialPos, finalPos):
        path = [initialPos]
        k = 0
        start = time.time()
        while path[-1] != finalPos:
            next_positions = [position for position in self.neighbors(path[-1])
                              if self._map[position] != WALL]
            candidate = choice(next_positions)
            cost = lambda position: self.euclideanDistance(position, finalPos)
            if cost(candidate) < cost(path[-1]):
                path.append(candidate)
                k += 1
                if k == EARLY_STOP:
                    path = []
                    break
            else:
                if random() < KEEP_PROBABILITY:
                    path.append(candidate)

        if path:
            path.append(finalPos)
        self.executionTimes["SimulatedA"] = (time.time() - start, len(path))
        return path


    def setDronePosition(self, position):
        if self._map[position] == EMPTY:
            self._drone.position = position

    @staticmethod
    def neighbors(position):
        x, y = position
        return [(x, y) for x, y in [(x, y - 1), (x + 1, y), (x, y + 1), (x - 1, y)]
                if 0 <= x < HEIGHT and 0 <= y < WIDTH]

    @staticmethod
    def processPredecessors(predecessors, destination):
        if destination not in predecessors:
            return []
        current_node = destination
        path = []
        while current_node != -1:
            path.insert(0, current_node)
            current_node = predecessors[current_node]
        return path

    @staticmethod
    def euclideanDistance(leftPos, rightPos):
        return np.linalg.norm(np.array(leftPos) - np.array(rightPos))

    @property
    def executionTimes(self):
        return self._execution_times
