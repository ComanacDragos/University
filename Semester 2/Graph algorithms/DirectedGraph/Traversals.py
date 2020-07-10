from DirectedGraph import *
from queue import PriorityQueue
import math

def BFS(vertex, graph):
    '''
    Breadth-first traversal
    :param vertex:
    :param graph:
    :return: the path
    :exception: vertex not valid
    '''
    if not vertex < graph.vertices:
        raise VertexException("Vertex doesn't exist")

    queue = graph.parse_outbound(vertex)
    visited = [vertex]


    #print("Visited at start: " + str(visited))
    #print("Queue at start: " + str(queue))

    current = 0
    #cont = 0
    while len(queue) > current:

        vertex = queue[current]

        if vertex not in visited:
            '''
            print("\nStep " + str(cont + 1) + ": ")
            print("Vertex: " + str(vertex) + " and Current position in queue: " + str(current))
            print("Visited before parsing outbound vertices: " + str(visited))
            print("Queue before parsing outbound vertices: " + str(queue))

            cont += 1
            '''
            queue += graph.parse_outbound(vertex)
            visited.append(vertex)

            '''
            print("Visited after parsing outbound vertices: " + str(visited))
            print("Queue after parsing outbound vertices: " + str(queue))
            '''
        current += 1


    return visited

def DFS(vertex, graph):
    visited = []
    DFS_Utility(vertex, graph, visited)
    return visited

def DFS_Utility(vertex, graph, visited):
    '''
    Depth first traversal
    :param vertex:
    :param graph:
    :param visited:
    :return:
    :exception: invalid vertex
    '''
    if not vertex < graph.vertices:
        raise VertexException("Vertex doesn't exist")

    visited.append(vertex)

    for i in graph.parse_outbound(vertex):
        if i not in visited:
            DFS_Utility(i, graph, visited)

def connected_components(graph):
    '''
    :param graph: undirected graph
    :return: list of all connected components
    '''
    connectedComponents = []
    for i in range(graph.vertices):
        visited = 0
        for component in connectedComponents:
            if i in component:
                visited = 1
                break
        if visited == 0:
            #print("\nComponent " + str(len(connectedComponents) +1))
            connectedComponents.append(BFS(i, graph))
            #print()
    return connectedComponents

def Backwards_DFS(vertex, graph):
    visited = []
    Backwards_DFS_Utility(vertex, graph, visited)
    return visited

def Backwards_DFS_Utility(vertex, graph, visited):
    '''
    Depth first traversal
    :param vertex:
    :param graph:
    :param visited:
    :return:
    :exception: invalid vertex
    '''
    if not vertex < graph.vertices:
        raise VertexException("Vertex doesn't exist")

    visited.append(vertex)

    for i in graph.parse_inbound(vertex):
        if i not in visited:
            Backwards_DFS_Utility(i, graph, visited)

def stackDFS(graph, vertex, visited, processed):

    for i in graph.parse_outbound(vertex):
        if i not in visited:
            visited.append(i)
            stackDFS(graph, i, visited, processed)

    processed.append(vertex)

def strongly_connected_components(graph):
    '''
    :param graph:
    :return:strongly connected components of the graph
    '''
    processed = []
    visited = []
    for i in range(graph.vertices):
        if i not in visited:
            visited.append(i)
            stackDFS(graph, i, visited, processed)

    components = {}

    visited.clear()
    q = []
    c = -1

    while len(processed) != 0:
        s = processed.pop()
        if s not in visited:
            c += 1
            components[s] = c
            q.insert(0, s)
            visited.append(s)
            # backwards BFS to find the elements from current component
            while len(q) != 0:
                x = q.pop()
                for y in graph.parse_inbound(x):
                    if y not in visited:
                        visited.append(y)
                        q.insert(0, y)
                        components[y] = c

    return components

