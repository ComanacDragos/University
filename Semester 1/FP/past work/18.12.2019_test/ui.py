from service import *

class UI:
    def __init__(self):
        self.service = Service(Repository("drivers.txt", Driver), Repository("addresses.txt",Address))
        self.start()

    def ui_display_addresses_drivers (self):
        addresses = self.service.list_of_addresses()
        drivers = self.service.list_of_drivers()
        if len(addresses) == 0:
            print("There are no addresses")
            return

        if len(drivers) == 0:
            print("There are no drivers")
            return
        print("The addresses are: ")
        for i in addresses:
            print(i)

        print("\nThe drivers are: ")
        for i in drivers:
            print(i)

    def ui_list_of_drivers_sorted (self):
        id = input("Give id: ").strip()
        l = self.service.list_of_drivers_sorted(id)
        for i in self.service.format_list(l):
            print(i)

    def ui_closest_drivers(self):
        print(self.service.closest_pair())

    @staticmethod
    def menu():
        menu ='''
1. Display list of addresses and drivers
2. List of drivers sorted by the distance to that addresss
3. Pair of drivers who are closest to each other
x. Exit
        '''
        print(menu)

    def start(self):
        commands = {
            "1": self.ui_display_addresses_drivers,
            "2": self.ui_list_of_drivers_sorted,
            "3": self.ui_closest_drivers
        }
        while True:
            self.menu()
            choice = input(">")
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("Invalid command")

UI()