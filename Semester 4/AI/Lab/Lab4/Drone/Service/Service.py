import time
from random import randint
from random import seed

from Domain.CycleAnt import CycleAnt
from Domain.Drone import Drone
from Domain.Ant import Ant
import Domain.settings as config
from Repository.MapGraph import MapGraph
from Repository.MapRepository import *
from Repository.SensorGraph import *


class Service:
    def __init__(self):
        seed(SEED)
        self._mapRepo = MapRepository("Resources/test2.map")
        self._drone = Drone(self.generatePositions().pop())
        self._sensorGraph = SensorGraph({sensor: self._mapRepo.readSensors(sensor)
                                         for sensor in self.generatePositions(SENSORS, [self._drone.position])})

        seed(randint(1, 10000))

    def generatePositions(self, count=1, badPositions=()):
        positions = set()
        while len(positions) != count:
            position = randint(0, HEIGHT - 1), randint(0, WIDTH - 1)
            if self._mapRepo[position] == EMPTY and position not in badPositions:
                positions.add(position)
        return positions

    def epoch(self, graph, ants):
        run = True
        while run:
            run = False
            for ant in ants:
                run = run or ant.addMove()

        pheromones = [Q / ant.fitness for ant in ants]

        graph.decay()

        for index, ant in enumerate(ants):
            for i in range(len(ant.representation) - 1):
                x = ant.representation[i]
                y = ant.representation[i + 1]
                graph.setTrace(x, y, graph.trace(x, y) + pheromones[index])

        return min(
            [(ant.fitness, ant) for ant in ants],
            key=lambda pair: pair[0]
        )[1]

    def epochBestAnt(self, graph, ants):
        run = True
        while run:
            run = False
            for ant in ants:
                run = run or ant.addMove()

        bestAnt = min(
            [(ant.fitness, ant) for ant in ants],
            key=lambda pair: pair[0]
        )[1]

        delta = 1/bestAnt.fitness

        graph.decay()

        for i in range(len(bestAnt.representation) - 1):
            x = bestAnt.representation[i]
            y = bestAnt.representation[i + 1]
            graph.setTrace(x, y, graph.trace(x, y) + DECAY * delta)

        return bestAnt

    def solverPath(self, graph, antType, start, end):
        bestAnt = None

        for epoch in range(EPOCHS):
            ants = [antType(start, end, graph) for _ in range(NO_ANTS)]
            ant = self.epoch(graph, ants)

            if bestAnt is None or bestAnt[0].fitness > ant.fitness:
                bestAnt = ant, epoch

            # print(f"global best: {bestAnt[0].fitness} at {bestAnt[1]}")
            # print(f"local best: {ant.fitness} at {epoch}\n\n")
        print(f"found at: {bestAnt[1]} -- {start} --> {end}")
        return bestAnt[0].representation, bestAnt[1]

    def solver(self):
        initialEnergy = config.ANT_SIZE
        closeSensor = min([(sensor, self.euclideanDistance(sensor, self._drone.position))
                           for sensor in self._sensorGraph.nodes], key=lambda pair: pair[1])[0]

        sensors = [sensor for sensor in self._sensorGraph.nodes]
        print(sensors, closeSensor)
        print(f"Energy: {config.ANT_SIZE}")

        graph = MapGraph(self._mapRepo)
        firstPath = self.solverPath(graph, Ant, self._drone.position, closeSensor)[0]
        config.ANT_SIZE -= len(firstPath)
        print(f"Remaining energy: {config.ANT_SIZE}")

        paths = {}

        for i in range(len(sensors) - 1):
            sensor = sensors[i]
            for destination in sensors[i + 1:]:
                mapGraph = MapGraph(self._mapRepo)
                paths[(sensor, destination)] = self.solverPath(mapGraph, Ant, sensor, destination)[0]
                paths[(destination, sensor)] = paths[(sensor, destination)]

        self._sensorGraph.initGraph(paths)

        cycle = self.solverPath(self._sensorGraph, CycleAnt, closeSensor, None)[0]

        print(cycle)

        finalPath = firstPath
        for i in range(len(cycle) - 1):
            path = paths[cycle[i], cycle[i+1]][:]
            if path[0] != cycle[i]:
                path.reverse()

            print(f"{cycle[i]} -> {cycle[i+1]} = {len(path)}")
            config.ANT_SIZE -= (len(path) - 1)
            print(f"Remaining energy: {config.ANT_SIZE}")

            finalPath += path[1:]

        for sensor in self._sensorGraph.nodes:
            if sensor not in finalPath:
                print("Error")
        self.validatePath(finalPath)

        config.ANT_SIZE = initialEnergy
        return finalPath

    def detectedPositions(self, path):
        detectedPositions = set()
        for position in path:
            detectedPositions = detectedPositions.union(set(self._mapRepo.readSensors(position)))
        return detectedPositions

    @property
    def mapImage(self):
        return self._mapRepo.mapImage

    def mapWithDrone(self, image=None):
        drone = pygame.transform.scale(pygame.image.load("Resources/drona.png"), (SQUARE_HEIGHT, SQUARE_WIDTH))
        if image is None:
            image = self.mapImage
        image.blit(drone, (self._drone.position[1] * SQUARE_HEIGHT, self._drone.position[0] * SQUARE_WIDTH))
        return image

    def mapWithSensors(self, image=None):
        sensorImg = pygame.transform.scale(pygame.image.load("Resources/sensor.png"), (SQUARE_HEIGHT, SQUARE_WIDTH))
        if image is None:
            image = self.mapImage
        for sensor in self._sensorGraph.sensors:
            image.blit(sensorImg, (sensor[1] * SQUARE_HEIGHT, sensor[0] * SQUARE_WIDTH))
            #for path in self._sensorGraph.sensors[sensor]:
            #    image = self.mapWithPath(path, image, RED, finalColor=RED)

        return image

    def mapWithPath(self, path, image=None, color=GREEN, finalColor=PURPLE):
        markPath = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
        markPath.fill(color)
        if image is None:
            image = self.mapImage
        if not path:
            return image
        for move in path:
            image.blit(markPath, (move[1] * SQUARE_HEIGHT, move[0] * SQUARE_WIDTH))
        markPath.fill(finalColor)
        image.blit(markPath, (path[-1][1] * SQUARE_HEIGHT, path[-1][0] * SQUARE_WIDTH))
        return image

    def setDronePosition(self, position, sleepTime=0):
        if self._mapRepo[position] == EMPTY:
            self._drone.position = position
            time.sleep(sleepTime)
        else:
            raise Exception("Bad position")

    def functionFactory(self, functionString):
        functions = {

        }
        if functionString in functions:
            return functions[functionString]
        else:
            raise Exception("Bad function string")

    def neighbors(self, position, radius=1):
        neighbors = set()
        x, y = position
        ulX, ulY = x - radius, y - radius
        brX, brY = x + radius, y + radius

        for x in range(ulX, brX + 1):
            for y in range(ulY, brY + 1):
                if self._mapRepo.validPosition((x, y)):
                    neighbors.add((x, y))

        return neighbors

    @staticmethod
    def validatePath(path):
        prev = path[0]
        for pos in path[1:]:
            dx, dy = pos[0] - prev[0], pos[1] - prev[1]
            if (dx, dy) not in DIRECTIONS:
                print(f"teleportation {prev} -> {pos}")
            prev = pos

    @staticmethod
    def savePath(path, file=OUTPUT_FILE):
        with open(file, 'wb') as f:
            pickle.dump(path, f)

    @staticmethod
    def loadPath(file):
        with open(file, "rb") as f:
            return pickle.load(f)

    @staticmethod
    def euclideanDistance(leftPos, rightPos):
        return np.linalg.norm(np.array(leftPos) - np.array(rightPos))
