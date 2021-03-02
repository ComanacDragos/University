import pygame
from pygame.locals import *
from Domain.settings import *


class Drone:
    def __init__(self, x, y):
        self._x = x
        self._y = y
        self._visited = {}
        self._last = None
        self.stack = [(x, y)]
        self._path = []

    @property
    def path(self):
        return self._path

    @path.setter
    def path(self, value):
        self._path = value

    @property
    def stack(self):
        return self._stack

    @stack.setter
    def stack(self, value):
        self._stack = value

    @property
    def position(self):
        return self._x, self._y

    @position.setter
    def position(self, value):
        self._x, self._y = value

    @property
    def visited(self):
        return self._visited

    @property
    def last(self):
        return self._last

    def move(self, position):
        if position is not None:
            self.visit_node()
            self._x, self._y = position
            self.path.append(position)
        else:
            if len(self.path) != 0:
                self._x, self._y = self.path.pop()

    def visit_node(self):
        if self.last is not None:
            dx, dy = self._x - self.last[0], self._y - self.last[1]

            if (dx not in [-1, 0, 1] or dy not in [-1, 0, 1]) or (dx != 0 and dy != 0):
                print("Teleportation!! from: " + str(self.last) + " to: " + str((self._x, self._y)))

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
