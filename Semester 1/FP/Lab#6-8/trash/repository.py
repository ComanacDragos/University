from domain import *
from exceptions import *
from random_words import *
from datetime import date
import random
import copy



class Repository:
    def __init__ (self):
        self._bookList = []
        for i in range(100, 110):
            l = random.choice(books)
            self._bookList.append(Book(str(i), l[1], l[0]))  


        self._clientList = []
        for i in range(100,110):
            l = random.choice(names)
            self._clientList.append(Client(str(i), l))
        
        self._rentalList = []
        self.init_rentals()
        #self._rentalList.append(Rental("100", "100", "100", self.create_date(2019, 10, 11)))
        #self._rentalList.append(Rental("101", "101", "101", self.create_date(2019, 10, 11), self.create_date(2019, 10, 13)))
      

    def init_rentals (self):
        '''
        Initializes the list of rentals with 10 objects
        '''
        cont = 100
        while cont < 110:
            book = random.choice(self.bookList)
            client = random.choice(self.clientList)
            year = 2019
            month = 11
            day = random.choice(range(1,31))
            day2 = random.choice(range(1,31))# !!! problem it can genrate 22.nov.2019 and 21.nov 2019
            d1 = self.create_date(year, month, day)
            
            choice = random.choice([1,2,3])

            if choice == 1:
                d2 = None            
                rental = Rental(str(cont), book.bookId, client.clientId, d1)
                try:
                    self.add_rental(rental)        
                    cont += 1
                except:
                    pass
            
            else:
                d2 = self.create_date(year, month, day2)
                rental = Rental(str(cont), book.bookId, client.clientId, d1)
                try:
                    self.add_rental(rental)
                    cont += 1
                    self.return_book(rental.rentalId, d2)
                    
                except:
                    pass

                





    @staticmethod
    def create_date (year, month, day):
        d = date(year = year, month = month, day = day)
        return d

    def valid_ID (self, ID):
        '''
        Cheks if the id is correct or not
        '''
        try:
            nr = float(ID)
        except:
            raise badId
        else:
            if nr <= 0 or int(nr) != nr:
                raise badId
    
    @property
    def bookList (self):
        return self._bookList
    
    @property
    def clientList (self):
        return self._clientList
    
    @property
    def rentalList (self):
        return self.rentalList

#----------------------------Book functions----------------------------------------------#

    def add_book (self, book):
        '''
        Adds a book to the book list
        Input:
            book - object of class Book
        Exceptions:
            duplicateBook - duplicate book id
        '''
        self.valid_ID(book.bookId)
        for i in self._bookList:
            if i == book:
                raise duplicateID("Duplicate book id!")
        if len(str(book.author)) == 0 or len(str(book.title)) == 0:
            raise emptyString
        self._bookList.append(book)

    def list_books (self, listOfBooks = None):
        '''
        Returns the list of some books in a specific format
        Input:
            listOfBooks - a list of books (with the default list being all the books)
        Output:
            books - the required books in a specific format
        '''
        if listOfBooks == None:
            listOfBooks = self._bookList
        books = []
        count = 0
        for i in listOfBooks:
            count += 1
            books.append(str(count) + ". " + str(i))
        return books

    def remove_bookID (self, ID):
        '''
        Removes a book with a given id
        Input:
            ID - the id of the book to be removed
        Exception:
            bookIdDoesNotExist - required book doesn't exist
        '''
        self.valid_ID(ID)    

        for i in self._bookList:
            if int(i.bookId) == int(ID):
                self._bookList.remove(i)
                rentals = []
                for i in self._rentalList:
                    if ID == i.bookId:
                        rentals.append(i)
                for i in rentals:
                    self._rentalList.remove(i)
                return
        raise IdDoesNotExist("Required book doesn't exist!")

    def update_book_author (self, ID, author):
        '''
        Updates the author of a given book 
        Input:
            ID - the id of the book to be removed
            author - the new author
        Exception:
            bookIdDoesNotExist - required book doesn't exist
        '''

        self.valid_ID(ID)

        if len(str(author)) == 0:
            raise emptyString
        
        for i in self._bookList:
            if i.bookId == ID:
                i.author = author
                return
        raise IdDoesNotExist("Required book doesn't exist")

    def update_book_title (self, ID, title):
        '''
        Updates the title of a given book 
        Input:
            ID - the id of the book to be removed
            title - the new title
        Exception:
            bookIdDoesNotExist - required book doesn't exist
        '''
        if len(str(title)) == 0:
            raise emptyString

        for i in self._bookList:
            if i.bookId == ID:
                i.title = title
                return
        raise IdDoesNotExist("Required book doesn't exist")

    def sort_book_list (self):
        '''
        Sorts the list with respect to the book ids
        '''
        self._bookList.sort()


# -------------------Client functions------------------------------------#

    def add_client (self, client):
        '''
        Adds a client to the client list 
        Input:
            client - object of type Client
        '''
        self.valid_ID(client.clientId)

        for i in self._clientList:
            if client == i:
                raise duplicateID
        self._clientList.append(client)
    
    def list_clients (self, clientList = None):
        '''
        Returns the list of some clients in a specific format
        Input:
            clientList - the list of some clients in a specific format (if no client list is given all clients are considered)
        Output:
            clients - the required clients in a specific format
        '''
        if clientList == None:
            clientList = self._clientList
        clients = []
        count = 0
        for i in clientList:
            count += 1
            clients.append(str(count) + ". " + str(i))
        return clients
    
    def remove_client (self,  ID):
        '''
        Removes a client with a given ID
        Input:
            ID - the id of the client to be removed
        '''
        self.valid_ID(ID) 

        for i in self._clientList:
            if int(i.clientId) == int(ID):
                self._clientList.remove(i)
                rentals = []
                for i in self._rentalList:
                    if ID == i.clientId:
                        rentals.append(i)
                for i in rentals:
                    self._rentalList.remove(i)
                return
        raise IdDoesNotExist

    def update_client_name (self, ID, name):
        '''
        Updates the name of a client 
        Input:
            ID - the id of the client to be updated
            name - the new name
        '''
        self.valid_ID(ID)
        for i in self._clientList:
            if int(i.clientId) == int(ID):
                i.name = name
                return
        raise IdDoesNotExist

    def sort_client_list (self):
        '''
        Sorts the client list with respect to client id
        '''
        self._clientList.sort()


# ------------------------------Rental functions----------------------------------------------#



    def client_exists (self, ID):
        '''
        Checks if there is an client with given ID
        Input:
            ID - the required client id
        '''
        for i in self._clientList:
            if i.clientId == ID:
                return True
        return False

    def book_exists (self, ID):
        '''
        Checks if there is a book with given ID
        Input:
            ID - the required book id
        '''
        for i in self._bookList:
            if i.bookId == ID:
                return True
        return False
    
    def add_rental (self, rental):
        '''
        Adds a rental to the list of rentals
        Input:
            rental - object of type rental
        '''
        self.valid_ID(rental.rentalId)
        self.valid_ID(rental.bookId)
        self.valid_ID(rental.clientId)

        for i in self._rentalList:
            if i.rentalId == rental.rentalId:
                raise duplicateID
            if i.bookId == rental.bookId:
                if i.returnedDate == None:
                    raise rentedBook
                elif i.returnedDate != None:
                    if rental.rentedDate <= i.returnedDate and rental.rentedDate >= i.rentedDate :
                        raise badDate

        if self.book_exists(rental.bookId) == False:
            raise bookDoesNotExist
        
        if self.client_exists(rental.clientId) == False:
            raise clientDoesNotExist
        
        self._rentalList.append(rental)

    def remove_rental (self, ID):
        '''
        Removes all rentals with given ID
        Input:
            ID - rental ID
        '''
        for i in self._rentalList:
            if i.rentalId == ID:
                self._rentalList.remove(i)

    @staticmethod
    def intersected_dates (x1, y1, x2, y2):
        '''
        Checks if the periods of time intersect 
        [x1, y1] - first time interval
        [x2, y2] - second time interval
        Where x1,y1,x2,y2 are dates and y2 may be None
        Output:
            True if they intersect
            False otherwise
        '''
        if y2 == None:
            if x2 > x1 and x2 < y1:
                return False
            return True
        else:
            
            if x1 > y1 or x2 > y2:
                return False
            if y1 < x2 or x1 > y2:
                return True
            return False
            
        

    def return_book (self, ID, date):
        '''
        Set the return date for a given rental
        Input:
            ID - rental ID
            date - the return date
        '''
        self.valid_ID(ID)
        for i in self._rentalList:
            if i.rentalId == ID:
                if i.returnedDate == None:
                    if i.rentedDate > date:
                        raise badDates
                    else:
                        for j in self._rentalList:
                            if i.bookId == j.bookId and self.intersected_dates(i.rentedDate, date, j.rentedDate, j.returnedDate) ==False:
                                raise badReturnDate
                        i.returnedDate = date
                        return
                else:
                    raise returnedBook
        raise rentalDoesNotExist

    def sort_rentals (self):
        '''
        Sorts the list of rentals with respect to rental id
        '''
        self._rentalList.sort()
 