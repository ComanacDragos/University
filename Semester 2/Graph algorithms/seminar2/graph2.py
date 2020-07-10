'''
This implementation uses dictionaries of dictionaries for DictGraph and DoubleDictGraph
For DictGraph the times are:
The time for 1000 vertices is:  0:00:00.156581
The time for 2000 vertices is:  0:00:00.580447
The time for 3000 vertices is:  0:00:01.293540
The time for 4000 vertices is:  0:00:02.318793
The time for 5000 vertices is:  0:00:03.639262
The time for 6000 vertices is:  0:00:05.386585
The time for 7000 vertices is:  0:00:06.483650
The time for 8000 vertices is:  0:00:08.577050
The time for 9000 vertices is:  0:00:10.553074
The time for 10000 vertices is:  0:00:14.281766

 For DoubleDictGraph the times are:
The time for 1000 vertices is:  0:00:00.032936
The time for 2000 vertices is:  0:00:00.064799
The time for 3000 vertices is:  0:00:00.095744
The time for 4000 vertices is:  0:00:00.127686
The time for 5000 vertices is:  0:00:00.192498
The time for 6000 vertices is:  0:00:00.209399
The time for 7000 vertices is:  0:00:00.273269
The time for 8000 vertices is:  0:00:00.274292
The time for 9000 vertices is:  0:00:00.313135
The time for 10000 vertices is:  0:00:00.344053

For MatrGraph the times are:
The time for 1000 vertices is:  0:00:00.462762
The time for 2000 vertices is:  0:00:01.835362
The time for 3000 vertices is:  0:00:04.189817
The time for 4000 vertices is:  0:00:07.311891
The time for 5000 vertices is:  0:00:12.085811
The time for 6000 vertices is:  0:00:17.432482
The time for 7000 vertices is:  0:00:22.357891
The time for 8000 vertices is:  0:00:31.187837
The time for 9000 vertices is:  0:00:39.308836
The time for 10000 vertices is:  0:00:47.263524


Larger times for DictGraph and DoubleDictGraph
For DictGraph the times are:
The time for 1000 vertices is:  0:00:00.160569
The time for 2000 vertices is:  0:00:00.586431
The time for 3000 vertices is:  0:00:01.329482
The time for 4000 vertices is:  0:00:02.092361
The time for 5000 vertices is:  0:00:03.216394
The time for 6000 vertices is:  0:00:04.662548
The time for 7000 vertices is:  0:00:06.256259
The time for 8000 vertices is:  0:00:08.187092
The time for 9000 vertices is:  0:00:10.396180
The time for 10000 vertices is:  0:00:12.996223
The time for 20000 vertices is:  0:01:02.208504
The time for 40000 vertices is:  0:05:03.755368

 For DoubleDictGraph the times are:
The time for 1000 vertices is:  0:00:00.029920
The time for 2000 vertices is:  0:00:00.060837
The time for 3000 vertices is:  0:00:00.098736
The time for 4000 vertices is:  0:00:00.126661
The time for 5000 vertices is:  0:00:00.159573
The time for 6000 vertices is:  0:00:00.194480
The time for 7000 vertices is:  0:00:00.251328
The time for 8000 vertices is:  0:00:00.272270
The time for 9000 vertices is:  0:00:00.318174
The time for 10000 vertices is:  0:00:00.356022
The time for 20000 vertices is:  0:00:00.704156
The time for 40000 vertices is:  0:00:01.618655

 For DoubleDictGraph the times are:
The time for 10000 vertices is:  0:00:00.355048
The time for 20000 vertices is:  0:00:00.784940
The time for 40000 vertices is:  0:00:01.531868
The time for 80000 vertices is:  0:00:03.162557
The time for 160000 vertices is:  0:00:06.588342
The time for 320000 vertices is:  0:00:14.101265
The time for 640000 vertices is:  0:00:27.615104
The time for 1000000 vertices is:  0:00:44.002279
'''
import random
from datetime import datetime

class MatrGraph:
    """A directed graph, represented by adjacency matrix.
    Vertices are numbers from 0 to n-1"""

    def __init__(self, n):
        """Creates a graph with n vertices (numbered from 0 to n-1)
        and no edges"""
        self._matr = []
        for i in range(n):
            self._matr.append([])
            for j in range(n):
                self._matr[i].append(False)

    def parseX(self):
        """Returns an iterable containing all the vertices"""
        nrOfVertices = len(self._matr)
        return range(nrOfVertices)

    def parseNout(self, x):
        """Returns an iterable containing the outbound neighbours of x"""
        list = []
        for i in range(len(self._matr[x])):
            if self._matr[x][i]:
                list.append(i)
        return list

    def parseNin(self, x):
        """Returns an iterable containing the inbound neighbours of x"""
        list = []
        for i in range(len(self._matr)):
            if self._matr[i][x]:
                list.append(i)
        return list

    def isEdge(self, x, y):
        """Returns True if there is an edge from x to y, False otherwise"""
        return self._matr[x][y]

    def addEdge(self, x, y):
        """Adds an edge from x to y.
        Precondition: there is no edge from x to y"""
        self._matr[x][y] = True


class DictGraph:
    """A directed graph, represented as a map from each vertex to
    the set of outbound neighbours"""

    def __init__(self, n):
        """Creates a graph with n vertices (numbered from 0 to n-1)
        and no edges"""
        self._dict = {}
        self.edges = 0
        for i in range(n):
            self._dict[i] = {}

    def parseX(self):
        """Returns an iterable containing all the vertices"""
        return self._dict.keys()

    def parseNout(self, x):
        """Returns an iterable containing the outbound neighbours of x"""
        return self._dict[x]

    def parseNin(self, x):
        """Returns an iterable containing the inbound neighbours of x"""
        list = []
        for i in self._dict.keys():
            if x in self._dict[i]:
                list.append(i)
        return list

    def isEdge(self, x, y):
        """Returns True if there is an edge from x to y, False otherwise"""
        return y in self._dict[x].values()

    def addEdge(self, x, y):
        """Adds an edge from x to y.
        Precondition: there is no edge from x to y"""
        self._dict[x][self.edges] = y
        self.edges += 1


class DoubleDictGraph:
    """A directed graph, represented as two maps,
    one from each vertex to the set of outbound neighbours,
    the other from each vertex to the set of inbound neighbours"""

    def __init__(self, n):
        """Creates a graph with n vertices (numbered from 0 to n-1)
        and no edges"""
        self._dictOut = {}
        self._dictIn = {}
        self.edges = 0
        for i in range(n):
            self._dictOut[i] = {}
            self._dictIn[i] = {}

    def parseX(self):
        """Returns an iterable containing all the vertices"""
        return self._dictOut.keys()

    def parseNout(self, x):
        """Returns an iterable containing the outbound neighbours of x"""
        return self._dictOut[x]

    def parseNin(self, x):
        """Returns an iterable containing the inbound neighbours of x"""
        return self._dictIn[x]

    def isEdge(self, x, y):
        """Returns True if there is an edge from x to y, False otherwise"""
        return y in self._dictOut[x].values()

    def addEdge(self, x, y):
        """Adds an edge from x to y.
        Precondition: there is no edge from x to y"""
        self._dictOut[x][self.edges] = y
        self._dictIn[y][self.edges] = x

def initRandomGraph(ctor, n, m):
    """Constructs and returns a randomly generated graph
    with n vertices and m edges.
    ctor must be a callable that gets the number of vertices and
    creates a graph with the given number of vertces and with no edges"""
    g = ctor(n)
    addedEdges = 0
    while addedEdges < m:
        x = random.randrange(0, n)
        y = random.randrange(0, n)
        if not g.isEdge(x, y):
            g.addEdge(x, y)
            addedEdges += 1
    return g

def run(ctor, vertices, edges):
    g = initRandomGraph(ctor , vertices, edges)
    for x in g.parseX():
        for y in g.parseNin(x):
            continue
        for y in g.parseNout(x):
            continue

def print_times(ctor):
    vertices = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
    for i in vertices:
        print("The time for " + str(i) + " vertices is: ", end=" ")
        t1 = datetime.now()
        run(ctor, i, i*10)
        t2 = datetime.now()
        print(t2-t1)

def larger_times(ctor):
    vertices = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 40000]
    for i in vertices:
        print("The time for " + str(i) + " vertices is: ", end=" ")
        t1 = datetime.now()
        run(ctor, i, i * 10)
        t2 = datetime.now()
        print(t2 - t1)

def larger_larger_times(ctor):
    vertices = [10000, 20000, 40000, 80000, 160000, 320000, 640000, 1000000]
    for i in vertices:
        print("The time for " + str(i) + " vertices is: ", end=" ")
        t1 = datetime.now()
        run(ctor, i, i * 10)
        t2 = datetime.now()
        print(t2 - t1)

def main():
    print("\nFor DictGraph the times are: ")
    print_times(DictGraph)
    print("\n For DoubleDictGraph the times are: ")
    print_times(DoubleDictGraph)
    print("\nFor MatrGraph the times are:")
    print_times(MatrGraph)


def larger_main():
    print("\nFor DictGraph the times are: ")
    larger_times(DictGraph)
    print("\n For DoubleDictGraph the times are: ")
    larger_times(DoubleDictGraph)


def larger_larger_main():
    print("\n For DoubleDictGraph the times are: ")
    larger_larger_times(DoubleDictGraph)


larger_larger_main()


