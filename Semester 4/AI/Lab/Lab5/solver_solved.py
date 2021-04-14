# -*- coding: utf-8 -*-
"""
In this file your task is to write the solver function!

"""
from random import randint


class Fuzzyfier:
    def __init__(self, left, right, mean=None):
        self._left = left
        self._right = right
        self._mean = mean
        if self._mean is None:
            self._mean = (self._left + self._right) / 2

    def fuzzyfy(self, x):

        if self._left is not None and self._left <= x < self._mean:
            return (x - self._left) / (self._mean - self._left)
        elif self._right is not None and self._mean <= x < self._right:
            return (self._right - x) / (self._right - self._mean)
        else:
            return 0

    def __repr__(self):
        return f"<{self._left}, {self._right}>"


class Solver:
    def __init__(self):
        self.isActive = True

        self._thetaRanges = {
            "NVB": (None, -25, -40),
            "NB": (-40, -10),
            "N": (-20, 0),
            "ZO": (-5, 5),
            "P": (0, 20),
            "PB": (10, 40),
            "PVB": (25, None, 40)
        }

        self._omegaRanges = {
            "NB": (None, -3, -8),
            "N": (-6, 0),
            "ZO": (-1, 1),
            "P": (0, 6),
            "PB": (3, None, 8)
        }

        self._fRanges = {
            "NVVB": (None, -24, -32),
            "NVB": (-32, -16),
            "NB": (-24, -8),
            "N": (-16, 0),
            "Z": (-4, 4),
            "P": (0, 16),
            "PB": (8, 24),
            "PVB": (16, 32),
            "PVVB": (24, None, 32)
        }

        self._bValues = {
            set_: index * 8 for index, set_ in enumerate(list(self._fRanges.keys()), start=-4)
        }

        fSets = list(self._fRanges.keys())
        # print(fSets)
        self._fuzzyTable = {
            thetaSet: {
                omegaSet: fSets[omegaIndex + thetaIndex]
                for omegaIndex, omegaSet in enumerate(self._omegaRanges.keys())
            }
            for thetaIndex, thetaSet in enumerate(list(self._thetaRanges.keys())[1:-1])
        }

        self._fuzzyTable["PVB"] = {
            omegaSet: fSets[index + 5]
            for (index, omegaSet) in enumerate(list(self._omegaRanges)[:-1])
        }
        self._fuzzyTable["PVB"]["PB"] = "PVVB"

        self._fuzzyTable["NVB"] = {
            omegaSet: fSets[index]
            for (index, omegaSet) in enumerate(list(self._omegaRanges)[1:])
        }
        self._fuzzyTable["NVB"]["NB"] = "NVVB"

        # for i in self._fuzzyTable:
        #     print(i, self._fuzzyTable[i])

        self._thetaFunctions = self.functions(self._thetaRanges)
        self._omegaFunctions = self.functions(self._omegaRanges)
        self._fRanges = self.functions(self._fRanges)

    def functions(self, ranges):
        return {set_: Fuzzyfier(*range_) for (set_, range_) in ranges.items()}

    def computeValues(self, value, functions):
        return {set_: function.fuzzyfy(value) for (set_, function) in functions.items()}

    def solver(self, theta, omega):
        if not self.isActive:
            return

        thetaValues = self.computeValues(theta, self._thetaFunctions)
        omegaValues = self.computeValues(omega, self._omegaFunctions)

        fValues = {}

        for thetaSet in self._fuzzyTable:
            for omegaSet, fSet in self._fuzzyTable[thetaSet].items():
                value = min(thetaValues[thetaSet], omegaValues[omegaSet])
                if fSet not in fValues:
                    fValues[fSet] = value
                else:
                    fValues[fSet] = max(value, fValues[fSet])

        s = sum(fValues.values())
        if s == 0:
            if theta == 0:
                return
            return 22 * theta/abs(theta)
        return sum(fValues[fSet] * self._bValues[fSet] for fSet in fValues.keys()) / s

def solver(t, w):
    """
    Parameters
    ----------
    t : TYPE: float
        DESCRIPTION: the angle theta
    w : TYPE: float
        DESCRIPTION: the angular speed omega

    Returns
    -------
    F : TYPE: float
        DESCRIPTION: the force that must be applied to the cart
    or

    None :if we have a division by zero

    """
    return randint(-300, 300)
