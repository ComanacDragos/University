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

def undoExampleHard():
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
    We add 2 clients
    '''
    clientSophia = clientController.create(103, "2990511035588", "Sophia")
    clientCarol = clientController.create(104, "2670511035588", "Carol")
   
    '''
    We add 2 cars
    '''
    carHyundaiTucson = carController.create(201, "CJ 02 TWD", "Hyundai", "Tucson")
    carToyotaCorolla = carController.create(202, "CJ 02 FWD", "Toyota", "Corolla")
    printReposWithMessage("Added 2 clients and 2 cars", clientRepo, carRepo, None)


    '''
    We delete 1 client and 1 car
    '''
    clientController.delete(103)
    carController.delete(202)
    printReposWithMessage("Deleted Sophia and the Corolla", clientRepo, carRepo, None)

    '''
    We undo twice
    '''
    undoController.undo()
    printReposWithMessage("1 undo, the Corolla is back", clientRepo, carRepo, None)
    undoController.undo()
    printReposWithMessage("1 undo, Sophia is back", clientRepo, carRepo, None)
    
    '''
    Redo twice 
    '''
    undoController.redo()
    undoController.redo()
    printReposWithMessage("2 redos, Sophia and the Corolla are again deleted", clientRepo, carRepo, None)
    
    '''
    Last redo
    '''
    undoController.redo()
    printReposWithMessage("1 redo - but there are no more redos", clientRepo, carRepo, None)

undoExampleHard()
