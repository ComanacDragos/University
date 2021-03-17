from random import choice

class Gene:
    def __init__(self):
        self._value = choice([(-1, 0), (1, 0), (0, 1), (0, -1)])

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, newValue):
        self._value = newValue