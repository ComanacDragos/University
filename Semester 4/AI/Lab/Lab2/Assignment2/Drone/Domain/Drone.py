import pygame
from Drone.Domain.settings import *


class Drone:
    def __init__(self, position):
        self._x, self._y = position

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

    @property
    def position(self):
        return self._x, self._y

    @position.setter
    def position(self, value):
        self._x, self._y = value

