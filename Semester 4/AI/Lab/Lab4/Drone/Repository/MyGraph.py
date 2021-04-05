from Domain.settings import *


class MyGraph:
    def __init__(self, paths, nodes, sensorData):
        self._nodes = nodes
        self._trace = {source: {destination: Q for destination in nodes} for source in nodes}
        self._sensorData = sensorData

        self._sensorStrengths = {
            sensor: max([len(positions) for positions in readings])
            for sensor, readings in sensorData.items()
        }

        self._graph = {node: {} for node in nodes}

        for source in nodes:
            for destination in nodes:
                if source == destination:
                    self._graph[source][destination] = 0
                    continue

                if (source, destination) in paths:
                    self._graph[source][destination] = len(paths[(source, destination)])
                    self._graph[destination][source] = len(paths[(source, destination)])
                else:
                    self._graph[source][destination] = len(paths[(destination, source)])
                    self._graph[destination][source] = len(paths[(destination, source)])

    @property
    def sensorStrengths(self):
        return self._sensorStrengths

    @property
    def nodes(self):
        return self._graph.keys()

    def trace(self, source, destination):
        return self._trace[source][destination]

    def setTrace(self, source, destination, value):
        self._trace[source][destination] = value

    def cost(self, source, destination):
        return self._graph[source][destination]

    def nextNodes(self, node):
        return self._graph[node].keys()

    def decay(self):
        for source in self._graph:
            for destination in self._graph[source]:
                self._trace[source][destination] *= (1-DECAY)

    def __len__(self):
        return len(self._graph)

    def __getitem__(self, node):
        return self._graph[node]

    def __setitem__(self, key, value):
        self._graph[key] = value

