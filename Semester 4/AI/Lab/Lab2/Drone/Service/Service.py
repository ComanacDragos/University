from Drone.Domain.Drone import *
from Drone.Domain.Environment import *
from Drone.Domain.DMap import *
from time import sleep
from random import randint


class Service:
    def __init__(self):
        self._sleep_time = 0.5
        self._environment = Environment()
        self._environment.randomMap()

        self._detectedMap = DMap()

        x, y = randint(0, 19), randint(0, 19)
        while self._environment[x][y] != 0:
            x, y = randint(0, 19), randint(0, 19)

        self._drone = Drone(x, y)  # 8, 17 -- 2, 18
        self.initial_pos = (x, y)

        self.markDetectableWalls()

    def speed_up(self):
        if self._sleep_time > 0.1:
            self._sleep_time -= 0.1

    def slow_down(self):
        self._sleep_time += 0.1

    def moveDFS(self):
        if len(self._drone.stack) != 0:
            x, y = self._drone.stack.pop()

            if (x, y) not in self.neighbors(*self._drone.position) and (x, y) != self._drone.position:
                print(f"Teleportation from: {self._drone.position} to {(x, y)}")

            self._drone.path.append((x, y))
            self._drone.visited[(x, y)] = True
            self._drone.position = (x, y)
            self.markDetectableWalls()

            next_pos = [(_x, _y) for _x, _y in self.neighbors(x, y) if
                        0 <= _x < HEIGHT and 0 <= _y < WIDTH and
                        self._detectedMap[_x][_y] != 1 and
                        (_x, _y) not in self._drone.visited]

            if len(next_pos) == 0:
                self._drone.path.pop()
                if len(self._drone.path) == 0:
                    self._drone.stack = []
                    return
                self._drone.stack.append(self._drone.path.pop())
            else:
                self._drone.stack += next_pos

            sleep(self._sleep_time)

    @staticmethod
    def neighbors(x, y):
        return [(x, y - 1), (x + 1, y), (x, y + 1), (x - 1, y)]

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
