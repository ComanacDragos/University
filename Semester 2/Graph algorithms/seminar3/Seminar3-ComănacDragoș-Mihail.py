import random


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

def accessible(g, s):
    """Returns the set of vertices of the graph g that are accessible
    from the vertex s"""
    acc = set()
    acc.add(s)
    list = [s]
    while len(list) > 0:
        x = list[0]
        list = list[1:]
        for y in g.parseNout(x):
            if y not in acc:
                acc.add(y)
                list.append(y)
    return acc


class GoatStatus:
    def __init__(self, i):
        self._status = i

    def __str__(self):
        return self.strX(~self._status) + "/" + self.strX(self._status)

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.__dict__ == other.__dict__
        else:
            return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        return self._status

    def isValid(self):
        """True if nobody eats nobody in this state"""
        return self.isValidBank(self._status) and self.isValidBank(~self._status)

    def parseN(self):
        ret = []
        for i in range(4):
            if (self._status & 1) == ((self._status >> i) & 1):
                ns = self._status ^ ((1 << i) | 1);
                s = GoatStatus(ns)
                if s.isValid():
                    ret.append(s)
        return ret

    def isValidBank(self, i):
        return (i & 4) == 0 or (i & 1) == 1 or ((i & 2) == 0 and (i & 8) == 0)

    def strX(self, i):
        ret = "("
        for j in range(4):
            if (i & (1 << j)) != 0:
                ret = ret + " " + self.names[j]
        return ret + ")"

    names = ("boat", "cabbage", "goat", "wolf")


class GoatGraph:
    def parseX(self):
        ret = []
        for i in range(16):
            s = GoatStatus(i)
            if s.isValid():
                ret.append(s)
        return ret

    def parseNout(self, s):
        return s.parseN()

    def parseNin(self, s):
        return s.parseN()


def initMyGraph(ctor):
    """Constructs and returns a hard-coded sample graph.
    ctor must be a callable that gets the number of vertices and
    creates a graph with the given number of vertces and with no edges"""
    g = ctor(9)
    g.addEdge(0, 1)
    g.addEdge(1, 0)
    g.addEdge(1, 1)
    g.addEdge(1, 2)
    g.addEdge(4, 0)
    g.addEdge(4, 2)
    g.addEdge(5,6)
    g.addEdge(2,5)
    g.addEdge(2,6)
    g.addEdge(6,7)
    g.addEdge(5,8)

    return g


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


def run():
    g = initMyGraph(DoubleDictGraph)
    for x in g.parseX():
        print("%s:" % x)
        for y in g.parseNin(x):
            print("%s <- %s" % (x, y))


run()

class BFSTree:
    def __init__(self, g, root):
        self._tree = {} # keys: parents, values: childs
        self._tree[None] = root

        s=root
        acc = set()
        acc.add(s)
        list = [s]
        while len(list) > 0:
            x = list[0]
            list = list[1:]
            for y in g.parseNout(x):
                if y not in acc:
                    acc.add(y)
                    self.add_vertex(x, y)
                    list.append(y)

    def add_vertex(self, parent, child):
        if parent not in self._tree:
            self._tree[parent] = [child]
            return
        self._tree[parent].append(child)

    def print_tree(self, vertex, Tab):
        print(Tab + str(vertex))
        if vertex in self._tree:
            for children in self._tree[vertex]:
                self.print_tree(children, Tab + "    ")

    def get_root(self):
        return self._tree[None]

    def reconstruct_path(self, path, vertex):
        if vertex in self._tree:
            path += self._tree[vertex]
            for children in self._tree[vertex]:
                self.reconstruct_path(path, children)

    def is_accessible(self, source, destination):
        if source == destination:
            return True
        accessible = []
        self.reconstruct_path(accessible, source)
        return destination in accessible

    def path_between_two_nodes(self, source, destination):
        if not self.is_accessible(source, destination):
            return []

        current = source
        path = [current]
        while current != destination:
            for i in self._tree[current]:
                if self.is_accessible(i, destination):
                    path.append(i)
                    current = i
                    break
        return path


g = initMyGraph(MatrGraph)
s = 4
tree = BFSTree(g, s)
print (accessible(g, s))

tree.print_tree(s, "")
path = [tree.get_root()]
tree.reconstruct_path(path, tree.get_root())

print("BFS paths is: ")
print(path)

print("\nPath between 4 and 8, where BFS starts from node 4")
print(tree.path_between_two_nodes(4,8))
print()

g = GoatGraph()

tree = BFSTree(g, GoatStatus(0))

tree.print_tree(GoatStatus(0), "")

print()

for i in tree.path_between_two_nodes(GoatStatus(0), GoatStatus(15)):
    print(i)