import networkx as nx
import json


class MyGraph:
    def __init__(self, gmlFile, settingsFile):
        self._gml = nx.read_gml(gmlFile, label="id")
        self._graph = []
        for _ in range(len(self._gml.nodes)):
            self._graph.append(set())
        self._mapping = {label: index for index, label in enumerate(self._gml.nodes)}

        for source, destination \
                in [(self._mapping[source], self._mapping[destination]) for source, destination in self._gml.edges]:
            self._graph[source].add(destination)
            self._graph[destination].add(source)

        with open(settingsFile) as file:
            self._settings = json.load(file)
            self._settings['min'] = 0
            self._settings['max'] = len(self._graph) - 1
            self._settings['noDim'] = len(self._graph)

    @property
    def settings(self):
        return self._settings

    @property
    def nodes(self):
        return list(range(len(self._graph)))

    @property
    def noEdges(self):
        return len(self._gml.edges)

    def __len__(self):
        return len(self._graph)

    def __getitem__(self, node):
        return self._graph[node]

