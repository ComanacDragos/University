from Drone.Domain.Drone import Drone
from Drone.Repository.MapRepository import *
from Drone.Repository.PopulationRepository import *
from random import randint
from Drone.Repository.RunRepository import *
from random import seed
from numba import jit, cuda
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
        parents = self._populationRepo.selection(2 * STEADY_STATE_NO_OFFSPRINGS)
        for _ in range(STEADY_STATE_NO_OFFSPRINGS):
            (firstPos, firstParent), (secondPos, secondParent) = parents.pop(randint(0, len(parents) - 1)), \
                                                                 parents.pop(randint(0, len(parents) - 1))
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
        foundAt, globalBest = 0, self._populationRepo.bestChromosome()
        averages = []
        bests = [globalBest.fitness]
        for generation in range(1, GENERATIONS + 1):
            iterationStrategy(fitnessFunction)
            localBest = self._populationRepo.bestChromosome()
            if localBest.fitness < globalBest.fitness:
                foundAt, globalBest = generation, localBest
            averages.append(self._populationRepo.fitnessAverage)
            bests.append(localBest.fitness)

            if generation % 10 == 0 and not self._log:
                print(generation)

        return foundAt, globalBest, averages, bests

    def solver(self):
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
            'detected positions': len(detectedPositions),
            'drone position': self._drone.position,
            'final position': path[-1]
        }
        self.savePath(path)
        if self._log:
            self._runRepo.saveRun(mySeed, bestChromosome.fitness, len(detectedPositions))
        return data, path, detectedPositions, averages, bests

    def simpleFitness(self, representation):
        path = set(self.interpretRepresentation(representation))
        error = len(representation) - len(path)
        return -(len(self.detectedPositions(path)) - error * ERROR_FACTOR)

    def uniquePositionsFitness(self, representation):
        path = set(self.interpretRepresentation(representation))
        error = len(representation) - len(path)
        return -(len(path) - error * ERROR_FACTOR)

    def variationFitness(self, representation):
        count = -1
        prev = None
        for gene in representation:
            if gene != prev:
                count += 1
                prev = gene

        path = self.interpretRepresentation(representation)
        return -(count * len(set(path))/len(representation))

    def neighborsFitness(self, representation):
        path = set(self.interpretRepresentation(representation))
        error = sum([len(self.neighbors(position, NEIGHBORS_RADIUS).intersection(path)) for position in path])
        return -(len(path) - error * ERROR_FACTOR)

    def circularFitness(self, representation):
        dx, dy = 0, 0
        path = self.interpretRepresentation(representation)

        for x, y in representation[:len(path)]:
            dx += x
            dy += y
        error = len(representation) - len(set(path))
        return self.euclideanDistance((0, 0), (dx, dy)) + error * ERROR_FACTOR

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
            if not self._mapRepo.validPosition((x, y)) or self._mapRepo[(x, y)] == WALL:
                break
            path.append((x, y))
        # self.validatePath(path)
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

    def setDronePosition(self, position, sleepTime=0):
        if self._mapRepo[position] == EMPTY:
            self._drone.position = position
            time.sleep(sleepTime)
        else:
            raise Exception("Bad position")

    def functionFactory(self, functionString):
        functions = {
            "generational": self.generational,
            "steadyState": self.steadyState,
            "simpleFitness": self.simpleFitness,
            "uniquePositionsFitness": self.uniquePositionsFitness,
            "variationFitness": self.variationFitness,
            "neighborsFitness": self.neighborsFitness,
            "circularFitness": self.circularFitness
        }
        if functionString in functions:
            return functions[functionString]
        else:
            raise Exception("Bad function string")

    def computeStats(self, stat):
        stats = [data[stat] for data in self._runRepo.data]
        return np.average(stats), np.std(stats)

    def setLog(self, value):
        self._log = value

    def neighbors(self, position, radius=1):
        neighbors = set()
        x, y = position
        ulX, ulY = x-radius, y-radius
        brX, brY = x+radius, y+radius

        for x in range(ulX, brX + 1):
            for y in range(ulY, brY + 1):
                if self._mapRepo.validPosition((x, y)) and self._mapRepo[(x, y)] != WALL:
                    neighbors.add((x, y))

        return neighbors

    @staticmethod
    def validatePath(path):
        prev = path[0]
        for pos in path[1:]:
            dx, dy = pos[0] - prev[0], pos[1] - prev[1]
            if (dx, dy) not in DIRECTIONS:
                raise Exception("Bad path")
            prev = pos

    @staticmethod
    def euclideanDistance(leftPos, rightPos):
        return np.linalg.norm(np.array(leftPos) - np.array(rightPos))

    @staticmethod
    def savePath(path, file=OUTPUT_FILE):
        with open(file, 'wb') as f:
            pickle.dump(path, f)

    @staticmethod
    def loadPath(file):
        with open(file, "rb") as f:
            return pickle.load(f)

