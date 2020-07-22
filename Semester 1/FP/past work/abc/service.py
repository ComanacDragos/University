from reposittory import *
class Service:
    def __init__(self, RouteRepo, BusRepo):
        self.RouteRepo = RouteRepo
        self.BusRepo = BusRepo

    def print_array (self, array):
        l = []
        count = 0
        for i in array:
            count += 1
            s = str(count) + ". " + str(i)
            l.append(s)
        return l

    def list_of_routes (self):
        return self.print_array(self.RouteRepo)

    def list_buses_on_route (self, route):
        l = []
        for i in self.BusRepo:
            if i.routeCode == route:
                l.append(i)
        return self.print_array(l)


    def number_of_kilometers (self, busId):
        '''
        Given a busId, the funcion cumputes how many km that bus has traveled during it's service
        Input:
            busId - the id of the required bus
        Function returns a string which contains the data about the given bus and the number of km
        '''
        for i in self.BusRepo:
            if i.id == busId:
                route = self.RouteRepo.find(i.routeCode)
                km = int(route.lenght)*int(i.timesUsed)
                s = str(i) + " and the number of kilometers is: " + str(km)
                return s

