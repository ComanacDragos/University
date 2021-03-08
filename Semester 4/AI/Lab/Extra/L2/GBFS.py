from queue import PriorityQueue


def transform_input(filename):
    f = open(filename)
    v = f.readlines()
    graph = []

    for line in v[1:-2]:
        graph.append([int(x) for x in line.split(",")])

    return graph, (int(v[-2]), int(v[-1]))


def process_predecessors(predecessors, source, destination, cycle):
    current_node = destination
    path = [source]
    while source != current_node:
        path.insert(1, current_node)
        current_node = predecessors[current_node]

    if cycle:
        path.append(source)
    return [x + 1 for x in path]


def GBFS(graph, source, destination):
    found = False
    visited = set()
    toVisit = PriorityQueue()
    toVisit.put((0, source))
    last = None
    predecessors = {source: -1}

    while not toVisit.empty() and not found:
        cost, node = toVisit.get()
        visited.add(node)
        if len(visited) == len(graph) and last is None:
            last = node

        if node == destination and len(visited) > 1:
            found = True

        for child in range(len(graph)):
            if child not in visited:
                cost = graph[node][child]
                toVisit.put((cost, child))
                predecessors[child] = node

    if last is None:
        last = destination

    return process_predecessors(predecessors, source, last, source == destination)


def nearestNeighbour(graph, source, destination):
    visited = set()
    currentNode = source
    predecessors = {source: -1}

    while True:
        visited.add(currentNode)

        if (currentNode == destination and len(visited) > 1) or len(visited) == len(graph):
            break

        neighbours = [(node, cost) for node, cost in enumerate(graph[currentNode]) if node not in visited]

        if len(neighbours) == 0:
            break
        else:
            prev = currentNode
            currentNode = min(neighbours, key=lambda neighbour: neighbour[1])[0]
            predecessors[currentNode] = prev

    return process_predecessors(predecessors, source, currentNode, source == destination)


strategy = nearestNeighbour
graph, (source, destination) = transform_input("input01.txt")


print(strategy(graph, source - 1, destination - 1))

print(strategy(graph, 0, 0))

print(strategy(graph, 3, 2))
