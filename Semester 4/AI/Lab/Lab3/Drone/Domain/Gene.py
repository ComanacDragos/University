from random import choice
from Drone.Domain.settings import *


class Gene:
    def __init__(self):
        self._value = choice(DIRECTIONS)

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, newValue):
        self._value = newValue