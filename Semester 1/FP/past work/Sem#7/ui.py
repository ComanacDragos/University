from repository import *
class UI:
    def __init__ (self, carService, clientService, rentalService):
        self._carService = carService
        self._clientService = clientService
        self._rentalService = rentalService

    def _rentCar (self):
        '''
        1. Determine the client (get client id)
        2. Determine the car (get car id)
        3. Validation ?
        4. Create Rental
'''     
        try:
            clientID = input("client id= ")
            client = self._clientService.getClient(clientID)

            carID = input("car ID= ")
            car = self._carService.getCar(carID)
            rent = Rental(100, date(), date(), client, car)
            self._rentalService.addRental(rent)
        except RepoError as re:
            print (re)

    def deleteClient(self):
        '''
        When we delete a client, we delete their rentals
        '''
        try:
            clientID = input("client id= ")
            client = self._clientService.getClient(clientID)

            self._rentalService.deleteAllRentals (clientID)
        except RepoError as re:
            print(re)        
        
        except RepoError as re:
            print(re)


    def _mostRentedCars (self):
        result = self._rentalService.mostRentedCars()
        for r in result:
            print(r)
        # car info -> number of days



    def start (self):

        '''
        Start program, display menu, read user input
        '''
        pass