from domain.Client import Client

class ClientController:
    def __init__(self, rentalController, validator, repository):
        self.__validator = validator
        self.__repository = repository
        self._rentalController = rentalController

    def create(self, clientId, clientCNP, clientName):
        client = Client(clientId, clientCNP, clientName)
        self.__validator.validate(client)
        self.__repository.store(client)
        return client

    def delete(self, clientId):
        '''
            1. Delete the client
        '''
        client = self.__repository.delete(clientId)

        '''
            2. Delete their rentals
            NB! This implementation is not transactional, i.e. the two delete operations are performed separately
        '''
        rentals = self._rentalController.filterRentals(client, None) 
        for rent in rentals:
            self._rentalController.deleteRental(rent.getId(), False)
        return client

    def getClientCount(self):
        return len(self.__repository)

    def update(self, car):
        '''
            NB! Undo/redo is also needed here
        '''
        pass
