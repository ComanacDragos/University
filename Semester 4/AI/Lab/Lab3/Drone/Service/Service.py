from Drone.Domain.Drone import Drone
from Drone.Repository.MapRepository import *
from queue import PriorityQueue
from random import randint
from random import choice
import pickle
import numpy as np
import time


class MapController:
    def __init__(self):
        self._repo = MapRepository("Resources/test1.map")
        self._repo = MapRepository()

        position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)
        while self._repo[position] != EMPTY:
            position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)

        self._drone = Drone(position)

    @property
    def mapImage(self):
        return self._repo.mapImage

    def mapWithDrone(self):
        drone = pygame.transform.scale(pygame.image.load("Resources/drona.png"), (SQUARE_HEIGHT, SQUARE_WIDTH))
        image = self.mapImage
        image.blit(drone, (self._drone.position[1] * SQUARE_HEIGHT, self._drone.position[0] * SQUARE_WIDTH))
        return image

    def mapWithPath(self, path, color):
        markPath = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
        markPath.fill(color)

        image = self.mapImage
        for move in path:
            image.blit(markPath, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))
        return image

    def setDronePosition(self, position):
        if self._repo[position] == EMPTY:
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

