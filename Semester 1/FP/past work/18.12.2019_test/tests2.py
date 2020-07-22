import unittest
from service import *

class test_service (unittest.TestCase):
    def test_sorted_drivers (self):
        service = Service(Repository(), Repository())
        driver1 = Driver("Ion", "10", "10")
        driver2 = Driver("Ion2", "20", "20")
        driver3 = Driver("Ion3", "40", "40")

        address = Address("1", "address", "20", "20")

        service.driverRepo.store(driver1)
        service.driverRepo.store(driver2)
        service.driverRepo.store(driver3)
        service.addressRepo.store(address)

        l = service.list_of_drivers_sorted("1")
        self.assertEqual(len(l),3)

        self.assertEqual(l[0].driver, driver2)
        self.assertEqual(l[1].driver, driver1)
        self.assertEqual(l[2].driver, driver3)

        self.assertEqual(l[0].distance, 0)
        self.assertEqual(l[1].distance, 20)
        self.assertEqual(l[2].distance, 40)