import pygame
from pygame.locals import *
from Domain.settings import *


class Drone:
    def __init__(self, x, y):
        self._x = x  # 5
        self._y = y  # 0
        self._visited = {}
        self._last = None

    @property
    def position(self):
        return self._x, self._y

    @property
    def visited(self):
        return self._visited

    @property
    def last(self):
        return self._last

    def move(self, position):
        self.visit_node()
        self._x, self._y = position

    def visit_node(self):
        self._last = (self._x, self._y)
        if self.last in self.visited:
            self.visited[self.last] += 1
        else:
            self.visited[self.last] = 1

    def get_direction(self, position):
        x, y = position
        if x < self._x:
            return UP
        elif x > self._x:
            return DOWN
        elif y < self._y:
            return LEFT
        else:
            return RIGHT
