from controller import *
from datetime import datetime
class UI:
    def __init__(self, controller):
        self._controller = controller

    @staticmethod
    def menu():
        menu = """
1. Information about the graph
2. Change the graph
3. Traversals
4. Walks
5. DAG
x. Exit
 """
        print(menu)

    @staticmethod
    def information_menu():
        menu = """
1. Number of vertices
2. Iterate the set of vertices
3. Check existence of an edge
4. In degree and out degree of a vertex
5. Inbound vertices
6. Outbound vertices
7. Get cost of an edge
8. List all edges
9. State of the graph
x. Exit information menu
        """
        print(menu)

    @staticmethod
    def modify_menu():
        menu = """
1. Update cost of an edge
2. Add vertex
3. Remove vertex
4. Add edge
5. Remove edge
6. Load directed graph
7. Load undirected graph
8. Store graph
9. Replace current graph with a random one
10. Replace current graph with a random undirected one
11. State of the graph
x. Exit modify menu
        """
        print(menu)

    @staticmethod
    def traversal_menu():
        menu ="""
1. State of the graph
2. BreadthFirst Traversal
3. DepthFirst Traversal
4. Connected components
5. Backwards DFS
6. Strongly connected components
x. Exit traversal menu
        """
        print(menu)

    @staticmethod
    def walks_menu():
        menu="""
1. State of the graph
2. Lowest length path using forward breadth first
3. Forward Dijkstra
4. Backwards Dijkstra
5. Bellman_Ford
6. Minimum cost hamiltonian cycle
x. Exit walks menu
        """
        print(menu)

    def DAG_menu(self):
        menu="""
1. State of the graph
2. Topological sort using predecessor counters
3. Highest cost path
4. Number of distinct paths
x. Exit DAG menu
        """
        print(menu)

    def UI_get_nr_vertices(self):
        print("The number of vertices is: " + str(self._controller.get_nr_vertices()))


    def UI_iterate_vertices(self):
        print("The vertices are: ", end=" ")
        for i in self._controller.get_vertices():
            print(i, end=" ")
        print()

    def UI_is_edge(self):
        left = int(input("Give left end-point: "))
        right = int(input("Give right end-point: "))
        if self._controller.is_edge(left, right) == True:
            print("\nThere is an edge between %d and %d" % (left, right))
        else:
            print("\nThere isn't an edge between %d and %d" %(left, right))

    def UI_in_out_degree(self):
        vertex = int(input("Give vertex: "))
        try:
            degrees = self._controller.get_degrees(vertex)
            print("The in degree of %d is: %d" %(vertex, degrees[0]))
            print("The out degree of %d is: %d" %(vertex, degrees[1]))
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_in_bound_parse(self):
        vertex = int(input("Give vertex: "))
        print("The target vertices are: ", end=" ")
        try:
            inBound = self._controller.parse_inbound(vertex)
            for i in inBound:
                print(i, end=" ")
            print()
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_out_bound_parse(self):
        vertex = int(input("Give vertex: "))
        try:
            outBound = self._controller.parse_outbound(vertex)
            print("The target vertices are: ", end=" ")
            for i in outBound:
                print(i, end=" ")
            print()
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_get_cost(self):
        left = int(input("Give left end-point: "))
        right = int(input("Give right end-point: "))
        try:
            cost = self._controller.get_cost(left, right)
            print("The cost of %d->%d is:" % (left, right), end=" ")
            print(cost)
        except EdgeException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_modify_cost(self):
        left = int(input("Give left end-point: "))
        right = int(input("Give right end-point: "))
        newValue = int(input("Give new cost: "))
        try:
            self._controller.modify_cost(left, right, newValue)
            print("The cost was updated succesfully")
        except EdgeException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_add_vertex(self):
        try:
            self._controller.add_vertex()
            print("The vertex was added successfuly")
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_remove_vertex(self):
        vertex = int(input("Give vertex to be removed: "))
        try:
            self._controller.remove_vertex(vertex)
            print("The vertex was removed successfuly")
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_add_edge(self):
        left = int(input("Give left end-point: "))
        right = int(input("Give right end-point: "))
        cost = int(input("Give cost: "))
        try:
            self._controller.add_edge(left, right, cost)
            print("The edge was added successfuly")
        except EdgeException as err:
            print(err)
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_remove_edge(self):
        left = int(input("Give left end-point: "))
        right = int(input("Give right end-point: "))
        try:
            self._controller.remove_edge(left, right)
            print("The edge was removed successfuly")
        except EdgeException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_load_graph(self):
        filename = input("Give filename: ")
        filename="Graphs/"+filename
        try:
            t1 = datetime.now()
            self._controller.load_graph(filename)
            t2 = datetime.now()
            t = t2-t1
            print("The graph was loaded successfuly in: " + str(t))
        except Exception:
            print("The requested graph does not exist")
        except ValueError:
            print("Bad number\n")

    def UI_load_undirected_graph(self):
        filename = input("Give filename: ")
        filename = "Graphs/" + filename
        try:
            t1 = datetime.now()
            self._controller.load_undirected_graph(filename)
            t2 = datetime.now()
            t = t2-t1
            print("The graph was loaded successfuly in: " + str(t))
        except FileNotFoundError:
            print("The requested graph does not exist")
        except ValueError:
            print("Bad number\n")

    def UI_store_graph(self):
        filename = input("Give filename: ")
        filename = "Graphs/" + filename
        self._controller.store_graph(filename)
        print("The graph was stored successfuly")

    def UI_random_graph(self):
        vertices = int(input("Give number of vertices: "))
        edges = int(input("Give number of edges: "))
        self._controller.random_graph(vertices, edges)
        print("The graph was successfuly replaced with a random one")

    def UI_random_undirected_graph(self):
        vertices = int(input("Give number of vertices: "))
        edges = int(input("Give number of edges: "))
        self._controller.random_undirected_graph(vertices, edges)
        print("The graph was successfuly replaced with a random one")

    def UI_print_edges(self):
        print("The edges are: \n")
        print(self._controller.print_edges())

    def UI_print_state(self):
        print("The state is: \n")
        print(self._controller.get_state())

    def UI_BreadthFirstTraversal(self):
        vertex = input("Give vertex: ")
        try:
            traversal = self._controller.breadth_first(vertex)
            print("The traversal is:", end=' ')
            for i in traversal:
                print(str(i), end=' ')
            print("\n")
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_DepthFirstTraversal(self):
        vertex = input("Give vertex: ")
        try:
            traversal = self._controller.depth_first(vertex)
            print("The traversal is:", end=' ')
            for i in traversal:
                print(str(i), end=' ')
            print("\n")
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_ConnectedComponents(self):
        components = self._controller.connected_components()
        cont = 1
        for i in components:
            print(str(cont) + ". ", end=' ')
            for j in i:
                print(str(j) + " ", end=' ')
            print("\n")
            cont += 1

    def UI_Backwards_DFS(self):
        vertex = input("Give vertex: ")
        try:
            traversal = self._controller.backwards_depth_first(vertex)
            print("The traversal is:", end=' ')
            for i in traversal:
                print(str(i), end=' ')
            print("\n")
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_strongly_connected_components(self):
        components = self._controller.strongly_connected_components()
        cont = 1
        print("The strongly connected components are: ")
        for i in components:
            print(str(cont) + ". ", end=' ')
            for j in i:
                print(str(j) + " ", end=' ')
            print("\n")
            cont += 1

    def UI_lowest_length_path_forward_breath_first(self):
        start = input("Give start vertex: ")
        end = input("Give end vertex: ")
        try:
            path=self._controller.lowest_lenghth_path_forward_breadth_first(start,end)
            if len(path) == 0:
                print("The end vertex is not accessible\n")
            else:
                print(path[0], end='')
                path.pop(0)
                for i in path:
                    print("->", i, end='')
                print(" Cost: ", len(path))
        except VertexException as err:
            print(err)
        except ValueError:
            print("Bad number\n")

    def UI_forward_dijkstra(self):
        start = input("Give start vertex: ")
        end = input("Give end vertex: ")
        try:
            info = self._controller.forward_dijkstra(start, end)
            if info[1] == -1:
                print("The end vertex is not accessible")
            else:
                path = info[0]
                print(path[0], end='')
                path.pop(0)
                for i in path:
                    print("->", i, end='')
                print(" Cost: ", info[1])
        except VertexException as err:
            print(err)

    def UI_backwards_dijkstra(self):
        start = input("Give start vertex: ")
        end = input("Give end vertex: ")
        try:
            info = self._controller.backwards_dijkstra(start, end)
            if info[1] == -1:
                print("The start vertex is not accessible")
            else:
                path = info[0]
                print(path[0], end='')
                path.pop(0)
                for i in path:
                    print("<-", i, end='')
                print(" Cost: ", info[1])
        except VertexException as err:
            print(err)

    def UI_Bellman_Ford(self):
        start = input("Give start vertex: ")
        end = input("Give end vertex: ")
        try:
            info = self._controller.Bellman_Ford(start, end)
            path = info[0]
            print(path[0], end='')
            path.pop(0)
            for i in path:
                print("->", i, end='')
            print(" Cost: ", info[1])
        except GraphException as err:
            print(err)

    def UI_topological_sort_predecessor_count(self):
        sort = self._controller.topological_sort_predecessor_counter()
        if sort == None:
            print("The graph has cycles")
            return
        for i in sort:
            print(i, end=" ")
        print()

    def UI_highest_cost_path(self):
        start = input("Give start vertex: ")
        end = input("Give end vertex: ")
        try:
            info = self._controller.highest_cost_path(start, end)
            path = info[0]
            print(path[0], end='')
            path.pop(0)
            for i in path:
                print("->", i, end='')
            print(" Cost: ", info[1])
        except GraphException as err:
            print(err)

    def UI_distinct_paths(self):
        start = input("Give start vertex: ")
        end = input("Give end vertex: ")
        try:
            print("Number of paths: " + str(self._controller.distinct_paths(start, end)))
        except GraphException as err:
            print(err)

    def UI_TSP(self):
        try:
            info = self._controller.TSP()
            path = info[0]
            print(path[0],end='')
            path.pop(0)
            for i in path:
                print("->", i, end='')
            print(" Cost: ", info[1])
        except GraphException as err:
            print(err)

    def start_information_menu(self):
        commands = {
            "1": self.UI_get_nr_vertices,
            "2": self.UI_iterate_vertices,
            "3": self.UI_is_edge,
            "4": self.UI_in_out_degree,
            "5": self.UI_in_bound_parse,
            "6": self.UI_out_bound_parse,
            "7": self.UI_get_cost,
            "8": self.UI_print_edges,
            "9": self.UI_print_state
        }
        while(True):
            self.information_menu()
            choice = input("> ")
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command\n")

    def start_modify_menu(self):
        commands = {
            "1": self.UI_modify_cost,
            "2": self.UI_add_vertex,
            "3": self.UI_remove_vertex,
            "4": self.UI_add_edge,
            "5": self.UI_remove_edge,
            "6": self.UI_load_graph,
            "7": self.UI_load_undirected_graph,
            "8": self.UI_store_graph,
            "9": self.UI_random_graph,
            "10": self.UI_random_undirected_graph,
            "11": self.UI_print_state,
        }

        while (True):
            self.modify_menu()
            choice = input("> ")
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command\n")

    def start_traversal_menu(self):
        commands = {
            "1": self.UI_print_state,
            "2": self.UI_BreadthFirstTraversal,
            "3": self.UI_DepthFirstTraversal,
            "4": self.UI_ConnectedComponents,
            "5": self.UI_Backwards_DFS,
            "6": self.UI_strongly_connected_components,
        }

        while (True):
            self.traversal_menu()
            choice = input("> ")
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command\n")

    def start_walks_menu(self):
        commands = {
            "1": self.UI_print_state,
            "2": self.UI_lowest_length_path_forward_breath_first,
            "3": self.UI_forward_dijkstra,
            "4": self.UI_backwards_dijkstra,
            "5": self.UI_Bellman_Ford,
            "6": self.UI_TSP,
        }

        while (True):
            self.walks_menu()
            choice = input("> ")
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command\n")

    def start_DAG_menu(self):
        commands = {
            "1":self.UI_print_state,
            "2":self.UI_topological_sort_predecessor_count,
            "3":self.UI_highest_cost_path,
            "4":self.UI_distinct_paths,
        }
        while (True):
            self.DAG_menu()
            choice = input("> ")
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command\n")


    def start(self):
        commands ={
            "1": self.start_information_menu,
            "2": self.start_modify_menu,
            "3": self.start_traversal_menu,
            "4": self.start_walks_menu,
            "5": self.start_DAG_menu
        }
        while True:
            self.menu()
            print()
            choice = input(">")
            print()
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command")
