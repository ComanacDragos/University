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
        for i in range(n):
            self._dict[i] = []

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
        return y in self._dict[x]

    def addEdge(self, x, y):
        """Adds an edge from x to y.
        Precondition: there is no edge from x to y"""
        self._dict[x].append(y)


class DoubleDictGraph:
    """A directed graph, represented as two maps,
    one from each vertex to the set of outbound neighbours,
    the other from each vertex to the set of inbound neighbours"""

    def __init__(self, n):
        """Creates a graph with n vertices (numbered from 0 to n-1)
        and no edges"""
        self._dictOut = {}
        self._dictIn = {}
        for i in range(n):
            self._dictOut[i] = []
            self._dictIn[i] = []

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
        return y in self._dictOut[x]

    def addEdge(self, x, y):
        """Adds an edge from x to y.
        Precondition: there is no edge from x to y"""
        self._dictOut[x].append(y)
        self._dictIn[y].append(x)

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

def main():
    print("\nFor DictGraph the times are: ")
    print_times(DictGraph)
    print("\n For DoubleDictGraph the times are: ")
    print_times(DoubleDictGraph)
    print("\nFor MatrGraph the times are:")
    print_times(MatrGraph)

main()

'''
This implementation uses dictionaries of lists

For DictGraph the times are: 
The time for 1000 vertices is:  0:00:00.314185
The time for 2000 vertices is:  0:00:01.299523
The time for 3000 vertices is:  0:00:02.864308
The time for 4000 vertices is:  0:00:05.120298
The time for 5000 vertices is:  0:00:08.331809
The time for 6000 vertices is:  0:00:12.984215
The time for 7000 vertices is:  0:00:17.445798
The time for 8000 vertices is:  0:00:21.267089
The time for 9000 vertices is:  0:00:28.402024
The time for 10000 vertices is:  0:00:35.197784


This implementation uses dictionaries of lists
 For DoubleDictGraph the times are: 
The time for 1000 vertices is:  0:00:00.028923
The time for 2000 vertices is:  0:00:00.056848
The time for 3000 vertices is:  0:00:00.088762
The time for 4000 vertices is:  0:00:00.135677
The time for 5000 vertices is:  0:00:00.175518
The time for 6000 vertices is:  0:00:00.203428
The time for 7000 vertices is:  0:00:00.224407
The time for 8000 vertices is:  0:00:00.273289
The time for 9000 vertices is:  0:00:00.340062
The time for 10000 vertices is:  0:00:00.353105

For MatrGraph the times are:
The time for 1000 vertices is:  0:00:00.496633
The time for 2000 vertices is:  0:00:01.883011
The time for 3000 vertices is:  0:00:04.159861
The time for 4000 vertices is:  0:00:07.807081
The time for 5000 vertices is:  0:00:12.288637
The time for 6000 vertices is:  0:00:17.681682
The time for 7000 vertices is:  0:00:23.159248
The time for 8000 vertices is:  0:00:31.648304
The time for 9000 vertices is:  0:00:40.164558
The time for 10000 vertices is:  0:00:52.153401
'''
