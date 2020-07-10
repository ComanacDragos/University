from DirectedGraph import *
import math

def topological_sort_predecessor_counting(graph):
    '''
    :param graph: graph with costs
    :return: a list of vertices in topological sorting order, or None if the graph has cycles
    '''
    sorted = []
    queue = []
    count = {}
    for x in graph.get_vertices():
        count[x] = graph.get_in_degree(x)
        if count[x] == 0:
            queue.append(x)
    
    while len(queue) != 0:
        x = queue.pop(0)
        sorted.append(x)

        for y in graph.parse_outbound(x):
            count[y] -= 1
            if count[y] == 0:
                queue.append(y)

    if len(sorted) < len(graph.get_vertices()):
        return None
    return sorted

def highest_cost_path(graph, start, end):
    '''
    :param graph: DAG
    :return:
    '''
    topologicalOrder = topological_sort_predecessor_counting(graph)
    if topologicalOrder == None:
        return None

    predecessors = {}
    dist = [-math.inf]*graph.vertices
    dist[start] = 0
    predecessors[start] = -1
    for i in topologicalOrder:
        if i == end:
            break
        for v in graph.parse_outbound(i):
            if dist[v] < dist[i] + graph.get_cost(i,v):
                dist[v] = dist[i] + graph.get_cost(i,v)
                predecessors[v] = i

    return (predecessors, dist)

def utility_number_of_distinct_paths(graph, current, end):
    if current == end:
        return 1
    sum = 0
    for i in graph.parse_outbound(current):
        sum += utility_number_of_distinct_paths(graph, i, end)
    return sum

def number_of_distinct_paths_in_DAG(graph, start, end):
    topologicalOrder = topological_sort_predecessor_counting(graph)
    if topologicalOrder == None:
        return None
    return utility_number_of_distinct_paths(graph, start, end)


g=DoubleDictGraph()
loadGraph(g, "Graphs/Example2.txt")

