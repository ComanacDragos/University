from repository import *

class Service:
    def __init__(self, driverRepo, addressRepo):
        self.driverRepo = driverRepo
        self.addressRepo = addressRepo

    def format_list (self, array):
        count = 0
        l = []
        for i in array:
            count += 1
            s = str(count) + ". " + str(i)
            l.append(s)
        return l

    def list_of_addresses(self):
        return self.format_list(self.addressRepo)

    def list_of_drivers(self):
        return self.format_list(self.driverRepo)

    def distance (self, x1,y1,x2,y2):
        '''
        Manhattan distance
        x1,y1 - first coordonate
        x2,y2 - second coordonate
        '''
        return abs(int(x1)-int(x2)) + abs(int(y1)-int(y2))

    def list_of_drivers_sorted (self, id):
        '''
        For a given address, return the list of drivers sorted by the distance to that address
        Input:
            id - the id of the address
        Output:
            the sorted list
        '''
        for i in self.addressRepo:
            if id == i.id:
                x = i.x
                y = i.y

        l = []
        for i in self.driverRepo:
            distance = self.distance(x,y, i.x, i.y)
            obj = driver_distance(i, distance)
            l.append(obj)
        l.sort()
        return l

    def distance_between_two_drivers (self, driver1, driver2):
        return self.distance(driver1.x, driver1.y, driver2.x, driver2.y)

    def closest_pair (self):
        d1 = self.driverRepo[0]
        d2 = self.driverRepo[1]
        l = [d1, d2]
        mx = self.distance_between_two_drivers(d1, d2)

        for i in self.driverRepo:
            for j in self.driverRepo:
                if i.name != j.name:
                    distance = self.distance_between_two_drivers(i,j)
                    if mx > distance:
                        mx = distance
                        l[0] = i
                        l[1] = j

        s = str(l[0]) + '\n'
        s += str(l[1]) + '\n'
        s += "The distance is: " + str(mx)
        return s



