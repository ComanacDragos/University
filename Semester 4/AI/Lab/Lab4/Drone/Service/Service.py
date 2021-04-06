import time
from random import randint

import Domain.settings as config
from Domain.Ant import Ant
from Domain.CycleAnt import CycleAnt
from Domain.Drone import Drone
from Repository.MapGraph import MapGraph
from Repository.MapRepository import *
from Repository.MyGraph import MyGraph
from Repository.SensorGraph import *


class Service:
    def __init__(self):
        self._mapRepo = MapRepository("Resources/test2.map")
        self._drone = Drone(self.generatePositions().pop())

        self._sensorData = {sensor: self._mapRepo.readSensors(sensor)
                            for sensor in self.generatePositions(SENSORS, [self._drone.position])}

        self._sensorGraph = SensorGraph(self._sensorData)

        self._sensorStrengths = {sensor: 0 for sensor in self._sensorGraph.nodes}

        self.displaySensorStrengths = True

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

        delta = 1 / bestAnt.fitness

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

            if bestAnt is not None and epoch - bestAnt[1] > EARLY_STOP:
                print(f"Early stop at {epoch}", end=" -- ")
                break

        print(f"found at: {bestAnt[1]} -- {start} --> {end} : {len(bestAnt[0].representation)}")
        return bestAnt

    def solver(self):
        sensors = [sensor for sensor in self._sensorGraph.nodes]
        print(sensors)
        print(f"Energy: {config.ANT_SIZE}")

        paths = {}
        nodes = [self._drone.position] + sensors
        for i in range(len(nodes) - 1):
            source = nodes[i]
            for destination in nodes[i + 1:]:
                paths[(source, destination)] = self.solverPath(MapGraph(self._mapRepo), Ant, source, destination)[
                    0].representation
                paths[(destination, source)] = paths[(source, destination)]

        print("Computing cycle...")
        bestAnt = self.solverPath(MyGraph(paths, nodes, self._sensorData), CycleAnt, self._drone.position, None)[0]
        cycle = bestAnt.representation
        self._sensorStrengths = bestAnt.sensorEnergy
        print(cycle)
        print(self._sensorStrengths)
        print(f"Best ant fitness {bestAnt.fitness}\nBest ant cost: {bestAnt._cost}\nBest ant remaining energy: {bestAnt._remainingEnergy}")

        energyConsumed = sum(self._sensorStrengths.values())
        print(f"Energy consumed by sensors: {energyConsumed}")
        print(f"battery: {config.ANT_SIZE - energyConsumed}")

        finalPath = [self._drone.position]
        for i in range(len(cycle) - 1):
            path = paths[cycle[i], cycle[i + 1]][:]
            if path[0] != cycle[i]:
                path.reverse()

            energyConsumed += (len(path) - 1)
            print(f"{cycle[i]} -> {cycle[i + 1]} = {len(path)}")

            finalPath += path[1:]
        energyConsumed += 1
        print(f"Remaining energy: {config.ANT_SIZE - energyConsumed}")
        for sensor in self._sensorGraph.nodes:
            if sensor not in finalPath:
                print("Error")
        self.validatePath(finalPath)

        if len(finalPath) > ANT_SIZE:
            finalPath = finalPath[:ANT_SIZE]
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
            if self.displaySensorStrengths:
                for path in self._sensorGraph.sensors[sensor]:
                    image = self.mapWithPath(path, image, RED, finalColor=RED, alpha=50)
                    image = self.mapWithPath(path[:self._sensorStrengths[sensor]], image, YELLOW, finalColor=YELLOW, alpha=200)

        return image

    def mapWithPath(self, path, image=None, color=GREEN, finalColor=PURPLE, alpha=255):
        markPath = pygame.Surface((SQUARE_HEIGHT, SQUARE_WIDTH))
        markPath.fill(color)
        markPath.set_alpha(alpha)
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
