from UI import *
from random_words import *
import random


class Main:
    def __init__ (self):

        self.settings = self.read_settings()

        self.undoService = UndoService()

        if self.settings["repository"] == 'inmemory':
            self.init_memory_repo()
        elif self.settings["repository"] == "file":
            self.init_file_repo()
        elif self.settings["repository"] == "pickle":
            self.init_pickle_repo()

        self.UI = UI(self.booksService, self.clientsService, self.rentalsService, self.undoService)

        self.start_menu_ui()

    def read_settings (self):
        file = open("settings.properties", "r")
        lines = file.readlines()
        settings = {}
        for i in lines:
            i = i.strip()
            line = i.split(" = ")
            settings[line[0]] = line[1]
        return settings

    def init_pickle_repo (self):
        self.bookRepo = PickleRepository(self.settings['books'], Book)
        self.booksService = BooksService(self.bookRepo, self.undoService)

        self.clientRepo = PickleRepository(self.settings['clients'], Client)
        self.clientsService = ClientsService(self.clientRepo, self.undoService)

        self.rentalRepo = PickleRepository(self.settings['rentals'], Rental)
        self.rentalsService = RentalsService(self.rentalRepo, self.booksService, self.clientsService, self.undoService)

    def init_file_repo (self):

        self.bookRepo = FileRepository(self.settings['books'], Book)
        self.booksService = BooksService(self.bookRepo, self.undoService)

        self.clientRepo = FileRepository(self.settings['clients'], Client)
        self.clientsService = ClientsService(self.clientRepo, self.undoService)

        self.rentalRepo = FileRepository(self.settings['rentals'], Rental)
        self.rentalsService = RentalsService(self.rentalRepo, self.booksService, self.clientsService, self.undoService)


    def init_memory_repo (self):

        self.bookRepo = Repository(self.init_book_repo())
        self.booksService = BooksService(self.bookRepo, self.undoService)

        self.clientRepo = Repository(self.init_client_repo())
        self.clientsService = ClientsService(self.clientRepo, self.undoService)

        self.rentalRepo = Repository([])
        self.rentalsService = RentalsService(self.rentalRepo, self.booksService, self.clientsService, self.undoService)
        self.init_rentals()

        self.undoService.clear_history()

    def init_book_repo (self):
        aux = []
        for i in range(100, 110):
            l = random.choice(books)
            aux.append(Book(str(i), l[1], l[0]))  
        return aux

    def init_client_repo(self):
        aux = []
        for i in range(100,110):
            l = random.choice(names)
            aux.append(Client(str(i), l))
        return aux
 

    def init_rentals (self):
        '''
        Initializes the list of rentals with 10 objects
        '''
        cont = 100
        while cont < 110:
            book = random.choice(self.bookRepo)
            client = random.choice(self.clientRepo)
            year = 2019
            month = 11
            day = random.choice(range(1,31))
            day2 = random.choice(range(1,31))
            d1 = date(year, month, day)
            
            choice = random.choice([1,2,3])

            if choice == 1:
                d2 = None            
                rental = Rental(str(cont), book.Id, client.Id, d1)
                try:
                    self.rentalsService.add_rental(rental)        
                    cont += 1
                except:
                    pass
            
            else:
                d2 = date(year, month, day2)
                rental = Rental(str(cont), book.Id, client.Id, d1)
            
                try:
                    self.rentalsService.add_rental(rental)
                    cont += 1
                    self.rentalsService.return_book(rental.Id, d2)
                  
                    
                except:
                    pass

    @staticmethod
    def print_start_menu ():
        menu = '''
1. Manage books
2. Manage clients
3. Manage rentals
4. Search for books
5. Search for clients
6. Statistics
7. Undo
8. Redo
x. Exit
            '''
        print(menu)

    def start_menu_ui (self):
        commands = {
            "1" : self.UI.start_book_ui,
            "2" : self.UI.start_client_ui,
            "3" : self.UI.start_rental_ui,
            "4" : self.UI.search_book_ui,
            "5" : self.UI.search_client_ui,
            "6" : self.UI.statistics_ui,
            "7" : self.UI.undo_ui,
            "8" : self.UI.redo_ui
        }
        while True:
            self.print_start_menu()
            choice = input(">").strip(" ")
            if choice in commands:
                commands[choice]()
            elif choice == "x":
                return
            else:
                print("\nInvalid command\n")

Main()





