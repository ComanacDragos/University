from DirectedGraph import *
from Traversals import *
from queue import PriorityQueue
from Utility import *


def lowest_length_path_forward_breadth_first(graph, start):
    '''
    :param graph: directed graph
    :param start: starting vertex
    :return: lowest length path between a staring node and all accessible nodes, by using a forward breadth-first search from the starting vertex
    '''
    if start not in graph.get_vertices():
        raise VertexException("Vertex doesn't exist")

    queue = []
    predecesors = {}
    lengths = {}
    visited = set()
    queue.insert(0, start)
    visited.add(start)
    lengths[start] = 0
    predecesors[start] = -1

    while len(queue) != 0:
        x = queue.pop()
        for y in graph.parse_outbound(x):
            if y not in visited:
                queue.insert(0, y)
                visited.add(y)
                lengths[y] = lengths[x] + 1
                predecesors[y] = x

    return predecesors


def forward_Dijkstra(graph, start, end):
    '''
    :param graph: directed graph with positive costs
    :param start: starting vertex
    :param end: starting vertex
    :return: a map that maps each accessible vertex to its predecessor on a path from s to it
    '''
    if start not in graph.get_vertices():
        raise VertexException("End vertex doesn't exist\n")
    if end not in graph.get_vertices():
        raise VertexException("End vertex doesn't exist\n")

    queue = PriorityQueue()
    predecesors = {}
    predecesors[start] = -1
    distances = {}
    queue.put((0, start)) # first argument in tuple is priority
    distances[start] = 0
    found = False

    while queue.qsize() != 0 and not found:
        x = queue.get()[1]
        for y in graph.parse_outbound(x):
            if y not in distances.keys() or distances[x] + graph.get_cost(x,y) < distances[y]:
                distances[y] = distances[x] + graph.get_cost(x,y)
                queue.put((distances[y], y))
                predecesors[y] = x
        if x == end:
            found = True

    return  (predecesors, distances)

def printQueque(q):
    list=[]
    while q.qsize():
        x = q.get()
        list.append(x)
        print(x, end=' ')
    print()
    for x in list:
        q.put(x)

def backwards_dijkstra(graph, start, end):
    '''
        :param graph: directed graph with positive costs
        :param start: starting vertex
        :param end: starting vertex
        :return: a map that maps each accessible vertex to its predecessor on a path from s to it
        '''
    if start not in graph.get_vertices():
        raise VertexException("End vertex doesn't exist\n")
    if end not in graph.get_vertices():
        raise VertexException("End vertex doesn't exist\n")

    queue = PriorityQueue()
    successors = {}
    successors[end] = -1
    distances = {}
    queue.put((0, end))  # first argument in tuple is priority
    distances[end] = 0
    found = False

    while queue.qsize() != 0 and not found:
        x = queue.get()[1]
        for y in graph.parse_inbound(x):
            if y not in distances.keys() or distances[x] + graph.get_cost(y, x) < distances[y]:
                distances[y] = distances[x] + graph.get_cost(y, x)
                queue.put((distances[y], y))
                successors[y] = x

        if x == start:
            found = True

    return (successors, distances)

def dynamic_programming_minimum_cost_walk(graph, mxLen, start):
    '''
    :param graph:
    :param mxLen:
    :return: the cost of minimum cost walk of length at most k from s to x, or ∞ if no such walk exists
    '''
    walk = Matrix(mxLen, graph.vertices)

    for i in range(walk.columns):
        walk[0][i] = math.inf

    walk[0][start] = 0

    for k in range(1, mxLen):
        for x in range(graph.vertices):
            mn = math.inf
            for y in graph.parse_inbound(x):
                current = walk[k-1][y] + graph.get_cost(y,x)
                if mn > current:
                    mn = current
            walk[k][x] = min(mn, walk[k-1][x])
    return walk

def Bellman_Ford(graph, start):
    '''
    :param graph:
    :param start: starting vertex
    :return:
    '''
    #Step1: initialize
    prev = {}
    dist = {}
    for x in graph.get_vertices():
        dist[x] = math.inf
    dist[start] = 0
    prev[start] = -1


    edges = graph.get_costs()

    #Step2: "relax" edges
    for i in range(graph.vertices-1):
        for edge in edges.keys():
            x = edge[0]
            y = edge[1]
            if dist[y] > dist[x] + edges[edge]:
                dist[y] = dist[x] + edges[edge]
                prev[y] = x

    #Step3: Check for negative cost cycles
    for edge in edges.keys():
        x = edge[0]
        y = edge[1]
        if dist[y] > dist[x] + edges[edge]:
            return -1

    return (prev, dist)

def Floyd_Warshall(graph, start, end):
    PathMatrix = Matrix(graph.vertices, graph.vertices, 0)
    CostMatrix = Matrix(graph.vertices, graph.vertices, math.inf)
    for i in range(graph.vertices):
        CostMatrix[i][i] = 0

    for i in graph.get_costs():
        x=i[0]
        y=i[1]
        CostMatrix[x][y] = graph.get_costs()[i]

    for i in range(graph.vertices):
        for j in range(graph.vertices):
            if i != j and CostMatrix[i][j] != math.inf:
                PathMatrix[i][j] = i

    for k in range(graph.vertices):
        for i in range(graph.vertices):
            for j in range(graph.vertices):
                if CostMatrix[i][j] > CostMatrix[i][k] + CostMatrix[k][j]:
                    CostMatrix[i][j] = CostMatrix[i][k] + CostMatrix[k][j]
                    PathMatrix[i][j] = PathMatrix[k][j]


    path = []

    path.insert(0, end)

    while path[0] != start:
        path.insert(0, PathMatrix[start][path[0]])

    print(path, CostMatrix[start][end])

def save_sol(graph, path, history):
    cost=0
    for i in range(len(path)):
        if(i!= len(path)-1):
            cost += graph.get_cost(path[i], path[i+1])
    #    print(path[i], end=' ')
    #print(cost)
    #print()
    if cost < history[1]:
        history[0] =path[:]
        history[1] = cost

def consistent(graph, path, k):
    if len(path) > graph.vertices+1:
        return False
    if len(path) == 0 or (len(path) == 1 and path[0] == 0):
        return True

    if path[0] != 0:
        return False

    if len(path) != graph.vertices +1:
        return graph.is_edge(path[-2], k) and k not in path[:-1]
    else:
        return graph.is_edge(path[-2], k)

def sol(graph, path):
    if len(path) < 3:
        return False
    if path[0] == path[-1] and len(path) == graph.vertices+1:
        return True
    return False

def bkt(graph, path, history):
    path.append(0)
    for i in graph.get_vertices():
        path[-1] = i
        if consistent(graph, path, i):
            if sol(graph, path):
                save_sol(graph, path[:], history)
            else:
                bkt(graph, path[:], history)

def TSP_bkt(graph):
    history = [[],math.inf]
    bkt(graph, [], history)
    return history

#g = DoubleDictGraph()
#loadGraph(g, "Graphs/Hamiltonian3.txt")
#rint(TSP_bkt(g))