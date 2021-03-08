import pygame
from pygame.locals import *
from Drone.Domain.settings import *


class Drone:
    def __init__(self, x, y):
        self._x = x
        self._y = y
        self._visited = {}
        self._last = None
        self._stack = [(x, y)]
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
