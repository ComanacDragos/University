'''
from repository.ClientCSVFileRepository import ClientCSVFileRepository

from repository.CarCSVFileRepository import CarCSVFileRepository
from repository.RentalCSVFileRepository import RentalCSVFileRepository
from repository.PickleFileRepository import PickleFileRepository
'''


from domain.Car import Car
from repository.CarTextRepoFile import *

carRepo = CarTextRepository("cars.txt")

#carRepo.store(Car(100, "cj 01 uyt", "Dacia", "Duster"))

print(carRepo)





'''

carRepo = None
clientRepo = None
rentalRepo = None

print('-' * 10 + " Clients " + '-' * 10)
print(clientRepo)
print('-' * 10 + " Cars " + '-' * 10)
print(carRepo)
print('-' * 10 + " Rentals " + '-' * 10)
print(rentalRepo)
'''