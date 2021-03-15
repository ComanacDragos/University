from util import *


class Chromosome:
    def __init__(self, problParam=None):
        self.__problParam = problParam
        self.__repres = [generateNewValue(problParam['min'], problParam['max']) for _ in range(problParam['noDim'])]
        self.__fitness = 0.0

    @property
    def repres(self):
        return self.__repres

    @property
    def fitness(self):
        return self.__fitness

    @repres.setter
    def repres(self, l=[]):
        self.__repres = l

    @fitness.setter
    def fitness(self, fit=0.0):
        self.__fitness = fit

    def crossover(self, c):
        position = randint(0, len(self.__repres) - 1)
        targetLabel = self.__repres[position]
        indexes = [pos for pos, label in enumerate(self.repres) if label == targetLabel]

        newRepresentation = c.__repres[:]
        for index in indexes:
            newRepresentation[index] = targetLabel

        offspring = Chromosome(self.__problParam)
        offspring.repres = newRepresentation
        return offspring

    def mutation(self):
        pos = randint(0, len(self.__repres) - 1)
        self.__repres[pos] = generateNewValue(self.__problParam['min'], self.__problParam['max'])

    def __str__(self):
        return '\nChromo: ' + str(self.__repres) + ' has fit: ' + str(self.__fitness)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, c):
        return self.__repres == c.__repres and self.__fitness == c.__fitness