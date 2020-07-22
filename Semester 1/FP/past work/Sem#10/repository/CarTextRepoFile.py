from repository.Repository import *
from domain.Car import *

class CarTextRepository(Repository):
    '''
    1. we want a text-file backed repository for cars
    what do we want?
    1. Works the same as repository
        - your program can change between Repository and CarTextRepository without changes to the source code
        => modules are interchangeable and independent
        => this class has the same methods as Repository
    2. Load the cars from a text file when we built the repository
    3. Save all car changes to the text file
    4.
    '''
    def __init__(self, fileName):
        super().__init__()
        self._filename = fileName
        #load the car data from a file
        self._loadFile()


    '''
    This is a private method that must not be called from outside the class
    '''
    def _loadFile(self):
        '''
        1. Open self._filename for text file reading
        2. For each line in input file:
            a. Separate into tokens (by commas)
            b. Build the car object
            c. Store it into Repo
        3. Close input file
        '''
        #file = open(self._filename, "r")
        file = open(self._filename, "r")
        lines = file.readlines()
        for i in lines:
            i = i.strip()
            line = i.split(",")
            newCar = Car(*line)
            self.store(newCar)
        file.close()

    def store(self, object):
        '''
        1. Do the same thing as repo.store
        2. save the cars to file
        '''
        Repository.store(self, object) #this calls the in-memory store function
        '''
        2 options:
        #1. repo.store will work, you have a new car stored -> you have to save it to a file
        #2. repositoryException in Repository.store -> car will not be saved
        '''
        self._saveFile()

    def _saveFile(self):
        pass

