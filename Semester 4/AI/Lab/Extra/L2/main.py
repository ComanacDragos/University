from queue import PriorityQueue
from math import inf
from random import randint
from random import random


def transform_input(filename):
    f = open(filename, "r")
    v = f.readlines()
    graph = dict()

    for index, line in enumerate(v[1:-2], start=1):
        graph[index] = [int(x) for x in line.split(",")]

    return graph, (int(v[-2]), int(v[-1]))


# print(transform_input("input01.txt"))

graph, (source, destination) = transform_input("input01.txt")
print(graph)


def TSPOLD(graph, source, destination):
    dist = {x: inf for x in graph.keys()}
    visited = {x: False for x in graph.keys()}
    predecessors = {x: -1 for x in graph.keys()}

    dist[source] = 0
    pq = PriorityQueue()

    pq.put((0, source))
    while pq.qsize() != 0:
        currentNode = pq.get()[1]
        visited[currentNode] = True
        for node, cost in enumerate(graph[currentNode], start=1):
            if not visited[node] and dist[currentNode] + cost < dist[node]:
                dist[node] = dist[currentNode] + cost
                pq.put((dist[node], node))
                predecessors[node] = currentNode

    return predecessors, dist


def TSP_OLD2(graph, source, destination):
    dist = {}
    predecessors = {}
    dist[source] = 0
    pq = PriorityQueue()
    pq.put((0, source))

    predecessors[source] = -1
    while pq.qsize() != 0:
        currentNode = pq.get()[1]
        if source == destination:
            local_pq = PriorityQueue()
        for node, cost in enumerate(graph[currentNode], start=1):
            if node not in dist or dist[currentNode] + cost < dist[node]:
                if source != destination:
                    dist[node] = dist[currentNode] + cost
                    pq.put((dist[node], node))
                    predecessors[node] = currentNode
                else:
                    local_pq.put((cost, node))
        if source == destination and not local_pq.empty():
            cost, node = local_pq.get()
            dist[node] = dist[currentNode] + cost
            pq.put((dist[node], node))
            predecessors[node] = currentNode

    return predecessors, dist


def TSP(graph, source, destination):
    dist = {}
    predecessors = {}
    dist[source] = 0
    pq = PriorityQueue()
    pq.put((0, source))

    predecessors[source] = -1
    while pq.qsize() != 0:
        currentNode = pq.get()[1]

        for node, cost in enumerate(graph[currentNode], start=1):
            if node not in dist or dist[currentNode] + cost < dist[node]:
                dist[node] = dist[currentNode] + cost
                pq.put((dist[node], node))
                predecessors[node] = currentNode

    return predecessors, dist


"""

def cost(graph, sol):
    return sum(graph[sol[i]][sol[i-1] - 1] for i in range(1, len(sol)))


def swapPositions(list, pos1, pos2):
    list[pos1], list[pos2] = list[pos2], list[pos1]
    return list

def generate_sol(sol, T):
    N = []
    k = 0
    while len(N) != len(sol)-2 and k != 100:
        aux = swapPositions(sol, randint(1, len(sol)-2), randint(1, len(sol)-2))
        if aux not in T and aux not in N:
            N.append(aux[:])
        k += 1
    return N

def tabu_search(graph, source, destination):
    T = []
    x = [source] + [_x for _x in range(1, len(graph) + 1) if _x not in [source, destination]] + [destination]
    k = 0
    while k != 100:
        N_T = generate_sol(x, T)
        if len(N_T) == 0:
            break
        best = min(N_T, key=lambda sol: cost(graph, sol))
        if cost(graph, x) < cost(graph, best):
            x = best
        T += N_T
        k += 1
    return x

print(TSP(graph, source, destination))

print(TSP(graph, 1, 1))

print(TSP(graph, 4, 3))
"""


def greedy(graph, source, detination):
    sum = 0
    counter = 0
    i = 0
    j = 0
    visitedRouteList = [source]
    route = []
    n = len(graph.keys())
