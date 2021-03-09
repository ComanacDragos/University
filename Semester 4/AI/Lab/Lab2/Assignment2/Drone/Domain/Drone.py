import pygame
from Drone.Domain.settings import *


class Drone:
    def __init__(self, position):
        self._x, self._y = position

    @property
    def position(self):
        return self._x, self._y

    @position.setter
    def position(self, value):
        self._x, self._y = value

