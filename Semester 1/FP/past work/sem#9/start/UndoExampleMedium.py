'''
Created on Nov 17, 2018

@author: Arthur
'''


from controller.UndoController import UndoController
from controller.RentalController import RentalController
from controller.ClientController import ClientController
from controller.CarController import CarController
from datetime import date
from util import printReposWithMessage
from repository.Repository import Repository
from domain.Rental import RentalValidator
from domain.Client import ClientValidator
from domain.Car import CarValidator


def undoExampleMedium():
    undoController = UndoController()
    clientRepo = Repository()
    carRepo = Repository()

    '''
    Start rental Controller
    '''
    rentRepo = Repository()
    rentValidator = RentalValidator()
    rentController = RentalController(undoController, rentValidator, rentRepo, carRepo, clientRepo)
    
    '''
    Start client Controller
    '''
    clientValidator = ClientValidator()
    clientController = ClientController(undoController, rentController, clientValidator, clientRepo)
    
    '''
    Start car Controller
    '''
    carValidator = CarValidator()
    carController = CarController(undoController, rentController, carValidator, carRepo)

    '''
    We add 3 clients
    '''
    clientSophia = clientController.create(103, "2990511035588", "Sophia")
    clientCarol = clientController.create(104, "2670511035588", "Carol")
    clientBob = clientController.create(105, "2590411035588", "Bob")    
    printReposWithMessage("We added 3 clients", clientRepo, None, None)

    '''
    We delete 2 of the clients
    '''
    clientController.delete(103)
    clientController.delete(105)
    printReposWithMessage("Deleted Sophia and Bob", clientRepo, None, None)

    '''
    We undo twice
    '''
    undoController.undo()
    printReposWithMessage("1 undo, so Bob is back", clientRepo, None, None)
    undoController.undo()
    printReposWithMessage("Another undo, so Sophia is back too", clientRepo, None, None)
    
    '''
    We redo once
    '''
    undoController.redo()
    printReposWithMessage("1 redo, so Sophia is again deleted", clientRepo, None, None)

undoExampleMedium()
