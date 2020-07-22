from service import *

carRepo = Repository()

carRepo.store((car1 := Car(1,"CJ01ERE", "Dacia", "Lodgy", "Red")))

carRepo.store((car2 := Car(2,"CJ01ERT", "Volvo", "Lodgy", "Red")))




clientRepo = Repository()

clientRepo.store((cl1 := Client(1, "Pop Maria", 20)))
clientRepo.store((cl2 := Client(2, "Vlad Ioana", 25)))

rentalRepo = Repository()

rentalRepo.store(Rental(1,date(2010,11,20), date(2010,11,25), cl1, car1))
rentalRepo.store(Rental(2,date(2010,11,20), date(2010,11,25), cl2, car2))


carService = CarService(carRepo)
ClientService = ClientService(clientRepo)
RentalService = RentalService(rentalRepo, carRepo, clientRepo)


#ui and start program

# ui = UI(carService, clientService, rentalService)