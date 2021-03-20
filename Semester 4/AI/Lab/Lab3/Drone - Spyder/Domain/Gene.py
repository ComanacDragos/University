from random import choice
from random import randint
from Drone.Domain.settings import *


class Gene:
    def __init__(self):
        self._value = choice(DIRECTIONS)
        self._strength = randint(1, GENE_STRENGTH)

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, newValue):
        self._value = newValue

    @property
    def strength(self):
        return self._strength
