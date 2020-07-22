from domain import *
class Repository:
    def __init__(self, filename = None, Class = None):
        self.list = []
        self.filename = filename
        self.Class = Class
        self.loadFile()

    def __getitem__(self, item):
        return self.list[item]

    def __len__(self):
        return len(self.list)

    def loadFile (self):
        if self.filename == None:
            return
        f = open(self.filename, "r")
        lines = f.readlines()
        for i in lines:
            i = i.strip().split(",")
            obj = self.Class(*i)
            self.list.append(obj)
        f.close()

    def find (self, id):
        for i in self.list:
            if i.id == id:
                return i

    def store (self, obj):
        self.list.append(obj)