from Domain.Drone import *
from Domain.Environment import *
from Domain.DMap import *
from time import sleep
from random import randint


class Service:
    def __init__(self):
        self._sleep_time = 0.5
        self._strategy = self.stack_strategy
        self._environment = Environment()
        #self._environment.randomMap()

        self._detectedMap = DMap()

        x, y = randint(0, 19), randint(0, 19)
        while self._environment[x][y] != 0:
            x, y = randint(0, 19), randint(0, 19)

        self._drone = Drone(x, y)

    def speed_up(self):
        if self._sleep_time > 0.1:
            self._sleep_time -= 0.1

    def slow_down(self):
        self._sleep_time += 0.1

    def least_visited_neighbors_strategy(self, positions):
        return min(positions, key=lambda x: self._drone.visited[x] if x in self._drone.visited else 0)

    def least_visited_area_strategy(self, positions):
        # not working
        statistics = [0] * 4
        for (x, y), freq in self._drone.visited.items():
            statistics[self._drone.get_direction((x, y))] += freq

        positions_stats = {pos: statistics[self._drone.get_direction(pos)] for pos in positions}

        return min(positions_stats.items(), key=lambda item: item[1])[0]

    def stack_strategy(self, positions):
        self._drone.stack += positions
        pos = None
        while pos not in self._drone.visited:
            pass
        return pos

    """
    def moveDFS(self):
        x, y = self._drone.position
        neighbors = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]

        next_pos = [(x, y) for x, y in neighbors if 0 <= x < HEIGHT and 0 <= y < WIDTH and self._detectedMap[x][y] == 0]

        if len(next_pos) == 1:
            self._drone.move(next_pos[0])
        else:
            filtered_pos = [p for p in next_pos if p not in self._drone.visited]

            if len(filtered_pos) == 0:
                if self._drone.last in next_pos:
                    next_pos.remove(self._drone.last)
                self._drone.move(self._strategy(next_pos))
            else:
                self._drone.move(self._strategy(filtered_pos))

        sleep(self._sleep_time)
    """

    def moveDFS(self):
        if len(self._drone.stack) != 0:
            x, y = self._drone.stack.pop()
            if (x, y) in self._drone.visited.keys() or self._detectedMap[x][y] == 1:
                return

            self._drone.move((x, y))

            neighbors = [(x, y - 1), (x + 1, y),  (x, y + 1), (x - 1, y)]

            next_pos = [(x, y) for x, y in neighbors if
                        0 <= x < HEIGHT and 0 <= y < WIDTH and self._detectedMap[x][y] != 1]

            self._drone.stack += next_pos

            sleep(self._sleep_time)

    def saveEnvironment(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self._environment, f)
            f.close()

    def loadEnvironment(self, numfile):
        with open(numfile, "rb") as f:
            self._environment = pickle.load(f)
            f.close()

    def markDetectableWalls(self):
        self._detectedMap.markDetectedWalls(self._environment, *self._drone.position)

    @property
    def detectedMapImage(self):
        return self._detectedMap.image(*self._drone.position)

    @property
    def environmentImage(self):
        return self._environment.image()
