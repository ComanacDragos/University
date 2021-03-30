from Domain.settings import *
import numpy as np


class SensorGraph:
    def __init__(self, sensors):
        self._sensors = sensors
        self._graph = {sensor: {subSensor: self.euclideanDistance(sensor, subSensor) for subSensor in sensors}
                       for sensor in sensors}
        self._trace = {sensor: {subSensor: Q for subSensor in sensors} for sensor in sensors}

    @property
    def sensors(self):
        return self._sensors

    @property
    def nodes(self):
        return self._graph.keys()

    def initGraph(self, paths):
        self._graph = {sensor: {} for sensor in self._sensors}

        for sensor in self._sensors:
            for subSensor in self._sensors:
                if sensor == subSensor:
                    continue
                if (sensor, subSensor) in paths:
                    self._graph[sensor][subSensor] = len(paths[(sensor, subSensor)])
                    self._graph[subSensor][sensor] = len(paths[(sensor, subSensor)])
                else:
                    self._graph[sensor][subSensor] = len(paths[(subSensor, sensor)])
                    self._graph[subSensor][sensor] = len(paths[(subSensor, sensor)])

    def trace(self, source, destination):
        return self._trace[source][destination]

    def setTrace(self, source, destination, value):
        self._trace[source][destination] = value

    def cost(self, source, destination):
        return self._graph[source][destination]

    def nextNodes(self, node):
        return self._graph[node].keys()

    def decay(self):
        for sensor in self._graph:
            for subSensor in self._graph[sensor]:
                self._graph[sensor][subSensor] *= (1-DECAY)

    def __len__(self):
        return len(self._graph)

    def __getitem__(self, node):
        return self._graph[node]

    def __setitem__(self, key, value):
        self._graph[key] = value

    @staticmethod
    def euclideanDistance(leftPos, rightPos):
        return np.linalg.norm(np.array(leftPos) - np.array(rightPos))
