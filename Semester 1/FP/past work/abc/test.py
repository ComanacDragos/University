import unittest
from service import *

class test_service(unittest.TestCase):
    def test (self):
        service = Service(Repository(), Repository())
        route = Route("1", "10")
        bus = Bus("1", "1", "mercedes", "7")

        service.RouteRepo.store(route)
        service.BusRepo.store(bus)

        s = service.number_of_kilometers("1")
        self.assertEqual(s, str(bus) +" and the number of kilometers is: " + "70")
'''

service = Service(Repository(), Repository())
route = Route("1", "10")
bus = Bus("1", "1", "mercedes", "7")

service.RouteRepo.store(route)
service.BusRepo.store(bus)
s = service.number_of_kilometers("1")

for i in service.RouteRepo:
    print(i)

print(s)

'''