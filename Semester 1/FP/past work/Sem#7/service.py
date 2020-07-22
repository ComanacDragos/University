from repository import *
from domain import Client
'''
class TestClientAgain (unittest.TestCase):
    def test_client (self):
        # sum interesting
        # python 3.8 introduced walrus operator -> :=
        # if (n:= len(mylist)):

        c = Client(1, "Pop Andreea", 19 )
        assert c.id == 1
        assert c.name == "Pop Andreea"
        assert c.age == 19

        try:
            c.age = 17
            assert False # should not run
        except ValueError:
            assert True # we are okay
        except Exception:
            assert False # a dif exception was raised


    def test_client_again (self):
        c = Client(1, "Pop Mihnea", 20 )
        try:
            c.age = 20
            assert False # should not run
        except ValueError:
            assert True # we are okay
        except Exception:
            assert False # a dif exception was raised
'''


class CarService:
    def __init__(self, carRepo):
        self._carRepo = carRepo
    

class ClientService:
    def __init__ (self, clientRepo):
        self._clientRepo = clientRepo




# wen implement a data transfer object (DTO)
class CarRentalDays:
    def __init__ (self, car, days):
        self._car = car
        self._days = days
    
    def __str__ (self):
        return str(self._days) + " - " + str(self._car)

class RentalService:
    def __init__ (self, rentalRepo, carRepo, clientRepo):
        self._rentalRepo = rentalRepo
        self._carRepo = carRepo
        self._clientRepo = clientRepo

    def getAllRentals (self):
        '''
        Return all rentals
        '''
        pass

    def deleteRental (self, rentalID):
        pass

    def deleteAllRentals (self, clientID):
        '''
        Delete all rentals associated with given client
        ''' 
        i = 0
        while i < len(self._rentalRepo):
            rental = self._rentalRepo[i]
            if clientID == rental.client.Id:
                self._rentalRepo.delete(clientID)
            else:
                i += 1
        

    #???
    def mostRentedCars (self):
        d = dict()

        for i in range(len(self._rentalRepo)):
            rent = self._rentalRepo[i] # __getitem__
            if rent.Car not in d:
                # keys are cars, values are the number of rental days
                d[rent.Car] = len(rent)
            else:
                d[rent.Car] += len(rent)
