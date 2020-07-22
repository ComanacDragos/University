from domain import *

class Repository:
    def __init__(self, Filename = None, Class = None):
        self.array = []
        self.filename = Filename
        self._class = Class
        self.load_file()

    def __getitem__(self, item):
        return self.array[item]

    def __len__(self):
        return len(self.array)

    def load_file(self):
        if self.filename == None:
            return
        f = open(self.filename, "r")
        lines = f.readlines()
        for i in lines:
            i = i.strip().split(",")
            obj = self._class(*i)
            self.store(obj)
        f.close()

    def store (self, obj):
        self.array.append(obj)
