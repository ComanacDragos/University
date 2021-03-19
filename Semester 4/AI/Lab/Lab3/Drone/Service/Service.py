from Drone.Domain.Drone import Drone
from Drone.Repository.MapRepository import *
from Drone.Repository.PopulationRepository import *
from random import randint
from Drone.Repository.RunRepository import *
from random import seed

import matplotlib.pyplot as plt
import pickle
import numpy as np
import time


class Service:
    def __init__(self):
        self._mapRepo = MapRepository("Resources/test2.map")
        self._runRepo = RunRepository()
        self._populationRepo = None

        if self._runRepo.dronePosition is None:
            position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)
            while self._mapRepo[position] != EMPTY:
                position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)
        else:
            position = self._runRepo.dronePosition

        self._drone = Drone(position)
        self._log = False

    def steadyState(self, fitnessFunction):
        # args - list of parameters needed to run one iteration
        # a iteration:
        # selection of the parrents
        # create offsprings by crossover of the parents
        # apply some mutations
        # selection of the survivors
        for _ in range(STEADY_STATE_NO_OFFSPRINGS):
            (firstPos, firstParent), (secondPos, secondParent) = self._populationRepo.selection(2)
            offspring = firstParent.crossover(secondParent)
            offspring.mutate()

            offspring.fitness = fitnessFunction(offspring.representation)

            if (firstParent.fitness > secondParent.fitness) and (firstParent.fitness > offspring.fitness):
                self._populationRepo[firstPos] = offspring
            if (secondParent.fitness > firstParent.fitness) and (secondParent.fitness > offspring.fitness):
                self._populationRepo[secondPos] = offspring

    def generational(self, fitnessFunction):
        newPopulation = []
        for _ in range(len(self._populationRepo)):
            (_, firstParent), (_, secondParent) = self._populationRepo.selection(2)
            offspring = firstParent.crossover(secondParent)
            offspring.mutate()
            offspring.fitness = fitnessFunction(offspring.representation)
            newPopulation.append(offspring)
        self._populationRepo.setPopulation(newPopulation)

    def run(self, fitnessFunction, iterationStrategy):
        # args - list of parameters needed in order to run the algorithm

        # until stop condition
        #    perform an iteration
        #    save the information need it for the satistics

        # return the results and the info for statistics
        foundAt, globalBest = 0, self._populationRepo.bestChromosome()
        averages = []
        bests = [globalBest.fitness]
        for generation in range(1, GENERATIONS + 1):
            iterationStrategy(fitnessFunction)
            localBest = self._populationRepo.bestChromosome()
            if localBest.fitness < globalBest.fitness:
                foundAt, globalBest = generation, localBest
            averages.append(self._populationRepo.fitnessAverage)
            print(generation)
            bests.append(localBest.fitness)
        return foundAt, globalBest, averages, bests

    def solver(self):
        # args - list of parameters needed in order to run the solver

        # create the population,
        # run the algorithm
        # return the results and the statistics
        mySeed = randint(1, 1000000)
        seed(mySeed)
        self._populationRepo = PopulationRepository()
        self._populationRepo.evaluate(self.functionFactory(FITNESS_FUNCTION))

        start = time.time()
        foundAt, bestChromosome, averages, bests = self.run(self.functionFactory(FITNESS_FUNCTION),
                                                            self.functionFactory(ITERATION_STRATEGY))
        executionTime = time.time() - start

        path = self.interpretRepresentation(bestChromosome.representation)
        detectedPositions = self.detectedPositions(path)
        data = {
            'found at generation': foundAt,
            'best fitness': bestChromosome.fitness,
            'execution time': executionTime,
            'path length': len(path),
            'unique positions': len(set(path)),
            'detected positions': len(detectedPositions)
        }

        if self._log:
            self._runRepo.saveRun(mySeed, bestChromosome.fitness)
        return data, path, detectedPositions, averages, bests

    def simpleFitness(self, representation):
        path = self.interpretRepresentation(representation)
        error = len(representation) - len(path)
        return -(len(self.detectedPositions(path)) - error * ERROR_FACTOR)

    def uniquePositionsFitness(self, representation):
        path = self.interpretRepresentation(representation)
        error = len(representation) - len(path)
        return -(len(set(path)) - error * ERROR_FACTOR)

    def variationFitness(self, representation):
        count = -1
        prev = None
        for gene in representation:
            if gene != prev:
                count += 1
                prev = gene

        path = self.interpretRepresentation(representation)
        return -(count * len(set(path))/len(representation))

    def detectedPositions(self, path):
        detectedPositions = set()
        for position in path:
            detectedPositions = detectedPositions.union(set(self._mapRepo.readSensors(position)))
        return detectedPositions

    def interpretRepresentation(self, representation):
        x, y = self._drone.position
        path = [(x, y)]
        for dx, dy in representation:
            x, y = x + dx, y + dy
            if self._mapRepo.validPosition((x, y)) and self._mapRepo[(x, y)] == WALL:
                break
            path.append((x, y))
        return path

    @property
    def mapImage(self):
        return self._mapRepo.mapImage

    def mapWithDrone(self, image=None):
        drone = pygame.transform.scale(pygame.image.load("Resources/drona.png"), (SQUARE_HEIGHT, SQUARE_WIDTH))
        if image is None:
            image = self.mapImage
        image.blit(drone, (self._drone.position[1] * SQUARE_HEIGHT, self._drone.position[0] * SQUARE_WIDTH))
        return image

    def mapWithPath(self, path, image=None, color=GREEN):
        markPath = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
        markPath.fill(color)
        if image is None:
            image = self.mapImage

        for move in path:
            image.blit(markPath, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))
        return image

    def setDronePosition(self, position):
        if self._mapRepo[position] == EMPTY:
            self._drone.position = position
        else:
            raise Exception("Bad position")

    def functionFactory(self, functionString):
        if functionString == "generational":
            return self.generational
        elif functionString == "steadyState":
            return self.steadyState
        elif functionString == "simpleFitness":
            return self.simpleFitness
        elif functionString == "uniquePositionsFitness":
            return self.uniquePositionsFitness
        elif functionString == "variationFitness":
            return self.variationFitness
        else:
            raise Exception("Bad function string")

    def computeStats(self):
        fitnesses = [data['fitness'] for data in self._runRepo.data]
        return np.average(fitnesses), np.std(fitnesses)

    def setLog(self, value):
        self._log = value
