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


def process_predecessors(predecessors, source, destination):
    current_node = destination
    path = []
    while source != current_node or len(path) == 0:
        path.insert(0, current_node)
        current_node = predecessors[current_node]
    path.insert(0, current_node)
    return path

def TSP(graph, source, destination):
    dist = {}
    predecessors = {}
    dist[source] = 0
    pq = PriorityQueue()
    pq.put((0, source))
    last = -1
    predecessors[source] = -1
    while pq.qsize() != 0:
        currentNode = pq.get()[1]
        if source == destination:
            local_pq = PriorityQueue()
        for node, cost in enumerate(graph[currentNode], start=1):
            if node not in dist or dist[currentNode] + cost < dist[node]:
                if source == destination:
                    local_pq.put((cost, node))
                else:
                    dist[node] = dist[currentNode] + cost
                    pq.put((dist[node], node))
                    predecessors[node] = currentNode
        if source == destination and not local_pq.empty():
            cost, node = local_pq.get()
            dist[node] = dist[currentNode] + cost
            pq.put((dist[node], node))
            predecessors[node] = currentNode
            last = node

    predecessors[source] = last
    return process_predecessors(predecessors, source, destination), dist


print(TSP(graph, source, destination))

print(TSP(graph, 1, 1))

print(TSP(graph, 4, 3))
