from service import *

class UI:
    def __init__(self):
        self.RouteRepo = Repository("busRoutes.txt", Route)
        self.BusRepo = Repository("buses.txt", Bus)

        self.Service = Service(self.RouteRepo, self.BusRepo)


        self.start()

    def display_bus_routes_ui (self):
        for i in self.Service.list_of_routes():
            print(i)

    def display_buses_on_route_ui (self):
        route = input("\nGive route: ").strip()
        l = self.Service.list_buses_on_route(route)
        if len(l) == 0:
            print("There are no buses on this route")
            return

        for i in l:
            print(i)

    def number_of_km_traveled_ui(self):
        busId = input("\nGive bus id: ").strip()
        print(self.Service.number_of_kilometers(busId))

    @staticmethod
    def menu():
        menu = '''
1. Display all buses travelling along a certain route
2. Display all bus routes
3. Number of kilometers traveled by a bus      
        '''
        print(menu)

    def start(self):
        dict = {
            "1": self.display_buses_on_route_ui,
            "2": self.display_bus_routes_ui,
            "3": self.number_of_km_traveled_ui
        }
        while True:
            self.menu()
            choice = input(">").strip()
            if choice in dict:
                dict[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command")

UI()