# from controller.UndoController import FunctionCall, Operation, CascadedOperation
from domain.Car import Car

class CarController:
    def __init__(self, undoController, rentalController, validator, repository):
        self.__validator = validator
        self.__repository = repository
        self._rentalController = rentalController
        self._undoController = undoController
        
    def create(self, carId, licensePlate, carMake, carModel):
        car = Car(carId, licensePlate, carMake, carModel)
        self.__validator.validate(car)
        self.__repository.store(car)
        return car
        
    def delete(self, carId):
        '''
            1. Delete the car from the repository
        '''
        car = self.__repository.delete(carId)

        '''
            2. Delete its rentals
            NB! This implementation is not transactional, i.e. the two delete operations are performed separately
        '''
        rentals = self._rentalController.filterRentals(None, car) 
        for rent in rentals:
            self._rentalController.deleteRental(rent.id, False)
        return car
       
    def update(self, car):
        '''
            NB! Undo/redo is also needed here
        '''
        pass
