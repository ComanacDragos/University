from controller.CarRentalException import CarRentalException
from domain.Rental import Rental

class RentalController:
    """
    Controller for rental operations
    """
    def __init__(self, validator, rentalRepo, carRepo, clientRepo):
        self.__validator = validator
        self.__carRepo = carRepo
        self._cliRepo = clientRepo        
        self.__repository = rentalRepo

    def createRental(self, rentalId, client, car, start, end, recordUndo=True):
        rental = Rental(rentalId, start, end, client, car)
        self.__validator.validate(rental)
        
        '''
        Check the car's availability for the given period 
        '''
        if self.isCarAvailable(rental.car, rental.start, rental.end) == False:
            raise CarRentalException("Car is not available during that time!")
        self.__repository.store(rental)

        return rental

    def isCarAvailable(self, car, start, end):
        """
        Check the availability of the given car to be rented in the provided time period
        car - The availability of this car is verified
        start, end - The time span. The car is available if it is not rented in this time span
        Return True if the car is available, False otherwise
        """
        rentals = self.filterRentals(None, car)
        for rent in rentals:
            if start > rent.end or end < rent.start:
                continue
            return False
        return True

    def filterRentals(self, client, car):
        """
        Return a list of rentals performed by the provided client for the provided car
        client - The client performing the rental. None means all clients
        cars - The rented car. None means all cars 
        """
        result = []
        for rental in self.__repository.getAll():
            if client != None and rental.client != client:
                continue
            if car != None and rental.car != car:
                continue
            result.append(rental)
        return result

    def deleteRental(self, rentalId, recordUndo=True):
        rental = self.__repository.delete(rentalId)
        return rental




