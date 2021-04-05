from Domain.Map import *
import pickle


class MapRepository:
    def __init__(self, mapFile=None):
        self._map = Map()
        if mapFile is not None:
            self.loadMap(mapFile)
        else:
            self._map.randomMap()

    def saveMap(self, numFile):
        with open(numFile, 'wb') as f:
            pickle.dump(self._map, f)
            f.close()

    def loadMap(self, numFile):
        with open(numFile, "rb") as f:
            self._map = pickle.load(f)
            f.close()

    @property
    def mapImage(self):
        return self._map.image()

    def _readDirection(self, direction, position):
        dx, dy = direction
        x, y = position
        positions = []

        x, y = x + dx, y + dy
        while self.validPosition((x, y)) and self._map[(x, y)] == EMPTY:
            positions.append((x, y))
            x, y = x + dx, y + dy
        return positions

    def readSensors(self, position):
        readings = []
        for direction in DIRECTIONS:
            readings.append(self._readDirection(direction, position)[:SENSOR_STRENGTH])
        return readings

    def validPosition(self, position):
        return 0 <= position[0] < HEIGHT and 0 <= position[1] < WIDTH and self._map[(position[0], position[1])] != WALL

    def __getitem__(self, item):
        return self._map[item]
