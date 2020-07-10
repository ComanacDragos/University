from DirectedGraph import *
from Traversals import *
from Walks import *
from DAG import *

class Controller:
    def __init__(self, graph):
        self._graph = graph

    def get_nr_vertices(self):
        '''
        :return: number of vertices in graph
        '''
        return self._graph.vertices

    def get_vertices(self):
        """
        :return: an iterable of the set of vertices
        """
        return self._graph.get_vertices()

    def is_edge(self, x, y):
        '''
        Returns True if there is an edge between x and y and false otherwise
        :param x: left end-point
        :param y:  rigt end-point
        :return: True/False
        '''
        return self._graph.is_edge(x,y)

    def get_degrees(self, vertex):
        '''
        :param vertex:
        :return: a tupple consisting of the in and out degrees of the vertex
        '''
        return(self._graph.get_in_degree(vertex), self._graph.get_out_degree(vertex))

    def parse_inbound(self, vertex):
        """
        :param vertex: a vertex of the graph
        :return: the list of target vertices
        """
        return self._graph.parse_inbound(vertex)

    def parse_outbound(self, vertex):
        """
        :param vertex: a vertex of the graph
        :return: the list of target vertices
        """
        return self._graph.parse_outbound(vertex)

    def get_cost(self, x, y):
        """
        :param x: left end-point
        :param y: right end-point
        :return: cost of the edge(x,y)
        """
        return self._graph.get_cost(x,y)

    def modify_cost(self, x, y, newValue):
        """
        :param x: left end-point
        :param y: right end-point
        :param newValue: new cost
        :return: None
        """
        self._graph.modify_cost(x, y, newValue)

    def add_vertex(self):
        '''
        :return:
        '''
        self._graph.add_vertex()

    def remove_vertex(self,n):
        '''
        :param n: vertex to be removed
        :return:
        '''
        self._graph.remove_vertex(n)

    def add_edge(self,x , y, cost):
        '''
        :param x: left end-point of the edge
        :param y: right end-point of the edge
        :param cost: the cost of the edge
        :return:
        '''
        self._graph.add_edge(x, y, cost)

    def remove_edge(self, x, y):
        '''
        :param x: left end-point of the edge
        :param y: right end-point of the edge
        :return:
        '''
        self._graph.remove_edge(x, y)

    def load_graph(self, filename):
        loadGraph(self._graph, filename)

    def load_undirected_graph(self, filename):
        loadUndirectedGraph(self._graph, filename)

    def store_graph(self, filename):
        storeGraph(self._graph, filename)

    def random_graph(self, vertices, edges):
        self._graph = generateRandomGraph(vertices, edges)

    def random_undirected_graph(self, vertices, edges):
        self._graph = generateRandomUndirectedGraph(vertices, edges)

    def print_edges(self):
        edges = ""
        for edge in self._graph.get_costs():
            edges += str(edge) + "\n"
        return edges

    def get_state(self):
        return self._graph.get_state()

    def breadth_first(self, vertex):
        return BFS(int(vertex), self._graph)

    def depth_first(self, vertex):
        return DFS(int(vertex), self._graph)

    def backwards_depth_first(self, vertex):
        return Backwards_DFS(int(vertex), self._graph)

    def connected_components(self):
        return connected_components(self._graph)

    def strongly_connected_components(self):
        map = strongly_connected_components(self._graph)
        components = []

        for i in range(max(map.values())+1):
            components.append([])

        for i in map:
            components[map[i]].append(i)

        return components

    def lowest_lenghth_path_forward_breadth_first(self, start, end):
        predecesors = lowest_length_path_forward_breadth_first(self._graph, int(start))
        path = []
        current = int(end)
        if current in predecesors:
            while current != -1:
                path.insert(0, current)
                current = predecesors[current]
        return path

    def forward_dijkstra(self, start, end):
        start = int(start)
        end = int(end)

        info = forward_Dijkstra(self._graph, start, end)
        predecesors = info[0]
        distances = info[1]

        path = []
        distance = -1
        if end in predecesors.keys():
            current = end
            while current != -1:
                path.insert(0, current)
                current = predecesors[current]
            distance = distances[end]

        return (path, distance)

    def backwards_dijkstra(self, start, end):
        start = int(start)
        end = int(end)

        info = backwards_dijkstra(self._graph, start, end)
        sucesors = info[0]
        distances = info[1]

        path = []
        distance = -1

        if start in sucesors.keys():
            current = start

            while current != -1:
                path.insert(0, current)
                current = sucesors[current]

            distance = distances[start]

        return (path, distance)

    def Bellman_Ford(self, start, end):
        end = int(end)
        start = int(start)
        output = Bellman_Ford(self._graph, int(start))
        if output == -1:
            raise EdgeException("Negative cost cycle")
        print(output[1])
        if end not in output[1].keys():
            raise VertexException("End is not accessible")

        path = []
        current = end
        while current != -1:
            path.insert(0, current)
            current = output[0][current]

        return (path, output[1][end])

    def topological_sort_predecessor_counter(self):
        return topological_sort_predecessor_counting(self._graph)

    def highest_cost_path(self, start, end):
        start = int(start)
        end = int(end)

        info = highest_cost_path(self._graph, start, end)

        if info == None:
            raise GraphException("The graph has a cycle")

        if end not in info[0]:
            raise GraphException("The end node is not accesible")

        path = [end]
        prev = info[0]
        dist = info[1]

        current = prev[end]

        while current != -1:
            path.insert(0, current)
            current = prev[current]

        return (path, dist[end])

    def distinct_paths(self, start, end):
        info = number_of_distinct_paths_in_DAG(self._graph, int(start), int(end))
        if info == None:
            raise GraphException("The graph has a cycle")
        return info

    def TSP(self):
        info = TSP_bkt(self._graph)
        if info[0] == []:
            raise GraphException("The graph does not have a hamiltonian cycle")
        return info