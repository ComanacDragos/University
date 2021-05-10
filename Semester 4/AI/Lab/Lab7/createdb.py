import numpy as np
import torch
from utils import *


class Database:
    def __init__(self, file='dataset.dat'):
        self._file = file
        self._data_set = None

    @property
    def data_set(self):
        return self._data_set

    @property
    def file(self):
        return self._file

    def generateDataSet(self, size=1000):
        points = set()
        while len(points) != size:
            points.add(
                tuple(np.random.uniform(-10, 10, 2))
            )
        self._data_set = torch.tensor([point for point in points])

        self.save()

    def save(self):
        if self._data_set is not None:
            torch.save(self._data_set, self._file)

    def load(self):
        self._data_set = torch.load(self._file).float()



if __name__ == '__main__':
    db = Database()
    # db.generateDataSet()
    # print(db.dataSet)
    db.load()
    print(db.data_set.dim())
