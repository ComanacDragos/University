from exceptions import *
from domain import *
from iterable import *
import pickle

class Repository:
    def __init__ (self, objectList):
        self.objectList = Iterable(objectList)
    
    def valid_ID (self, ID):
        '''
        Cheks if the id is correct or not
        '''
        try:
            nr = float(ID)
        except:
            raise badId
        else:
            if nr <= 0 or int(nr) != nr:
                raise badId

    @property
    def get_list (self):
        return self.objectList

    @get_list.setter
    def get_list (self, list):
        self.objectList = list

    def store (self, object):
        self.valid_ID(object.Id)
        for i in self.get_list:
            if i.Id == object.Id:
                raise duplicateID ("duplicate id")
        self.get_list.append(object)

    def find (self, id):
        for i in range(0, len(self.get_list)):
            if self.get_list[i].Id == id:
                return i
        raise IdDoesNotExist

    def delete (self, id):
        self.valid_ID(id)
        index = self.find(id)
        if index == None:
            raise IdDoesNotExist("No such object")
            
        #self.get_list.pop(self.find(id))
        del self.get_list[self.find(id)]
    
    def __getitem__ (self, value):
        return self.get_list[value]

    def __len__ (self):
        return len(self.get_list)

    @staticmethod
    def comparison (x,y):
        if x > y:
            return False
        return True

    def sort (self):
        #self.get_list.sort()
        gnomeSort(self.get_list, self.comparison)


class FileRepository (Repository):
    def __init__ (self, filename, Class):
        super().__init__([])
        self._filename = filename
        self._Class = Class
        self._loadFile()


    def _loadFile (self):
        file = open(self._filename, "r")
        lines = file.readlines()
        for i in lines:
            i = i.strip()
            line = i.split(",")
            newObject = self._Class(*line)
            self.store(newObject)
        file.close()

    def store_current_state (self):
        file = open(self._filename, "w")
        lines = ""
        for i in self.get_list:
            lines += i.to_file() + '\n'
        file.write(lines)
        file.close()

    def store (self, object):
        Repository.store(self, object)
        self.store_current_state()

    def delete  (self, object):
        Repository.delete(self, object)

        self.store_current_state()

class PickleRepository (Repository):
    def __init__(self, filename, Class):
        super().__init__([])
        self._filename = filename
        self._Class = Class

        self._loadFile()

    def store_current_state (self):
        f = open(self._filename, "wb")
        pickle.dump(self.get_list, f)
        f.close()

    def _loadFile(self):
        try:
            f = open(self._filename, "rb")
            for i in pickle.load(f):
                self.store(i)
        except:
            pass

    def store(self, object):
        Repository.store(self, object)
        self.store_current_state()

    def delete(self, object):
        Repository.delete(self, object)
        self.store_current_state()


def init_pickle():
    bookRepo = FileRepository("books.txt", Book)

    clientRepo = FileRepository("clients.txt", Client)

    rentalRepo = FileRepository("rentals.txt", Rental)

    books = open("books.pickle", "wb")
    pickle.dump(bookRepo, books)

    clients = open("clients.pickle", "wb")
    pickle.dump(clientRepo, clients)

    rentals = open("rentals.pickle", "wb")
    pickle.dump(rentalRepo, rentals)

