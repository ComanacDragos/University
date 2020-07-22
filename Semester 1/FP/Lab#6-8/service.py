from newRepository import *
from datetime import date


class BooksService:
    def __init__ (self, booksRepo, undoService = None):
        self.booksRepo = booksRepo
        self.undoService = undoService
    
    def add_book (self, book):
        '''
        Adds a book to the book list
        Input:
            book - object of class Book
        Exceptions:
            duplicateBook - duplicate book id
        '''
        if len(str(book.author)) == 0 or len(str(book.title)) == 0:
            raise emptyString
        self.booksRepo.store(book)

        undoOp = FunctionCall(self.remove_bookID, book.Id)
        redoOp = FunctionCall(self.add_book, book)
        operation = Operation(undoOp, redoOp)

        self.undoService.record(operation)

    def list_books (self, listOfBooks = None):
        '''
        Returns the list of some books in a specific format
        Input:
            listOfBooks - a list of books (with the default list being all the books)
        Output:
            books - the required books in a specific format
        '''
        if listOfBooks == None:
            listOfBooks = self.booksRepo
        books = []
        count = 0
        for i in listOfBooks:
            count += 1
            books.append(str(count) + ". " + str(i))
        return books

    def list_books_id (self, idList):
        '''
        Returns a list of book objects having ids from idList
        '''
        books = []
        for i in idList:
            index = self.booksRepo.find(i)
            book = self.booksRepo[index]
            books.append(book)
        for i in self.booksRepo:
            if i.Id not in idList:
                books.append(i)
        return books
        

    def remove_bookID (self, ID):
        '''
        Removes a book with a given id
        Input:
            ID - the id of the book to be removed
        Exception:
            bookIdDoesNotExist - required book doesn't exist
        '''
        self.booksRepo.delete(ID)

    def update_book_author (self, ID, author):
        '''
        Updates the author of a given book 
        Input:
            ID - the id of the book to be removed
            author - the new author
        Exception:
            bookIdDoesNotExist - required book doesn't exist
        '''

        self.booksRepo.valid_ID(ID)

        if len(str(author)) == 0:
            raise emptyString
        
        for i in self.booksRepo:
            if i.Id == ID:
                oldAuthor = i.author
                i.author = author
                try:
                    self.booksRepo.store_current_state()
                except: pass

                undoOp = FunctionCall(self.update_book_author, ID, oldAuthor)
                redoOp = FunctionCall(self.update_book_author, ID, author)
                operation = Operation(undoOp, redoOp)

                self.undoService.record(operation)

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
        self.booksRepo.valid_ID(ID)

        if len(str(title)) == 0:
            raise emptyString

        for i in self.booksRepo:
            if i.Id == ID:
                oldTitle = i.title
                i.title = title
                try:
                    self.booksRepo.store_current_state()
                except: pass

                undoOp = FunctionCall(self.update_book_title, ID, oldTitle)
                redoOp = FunctionCall(self.update_book_title, ID, title)
                operation = Operation(undoOp, redoOp)

                self.undoService.record(operation)

                return
        raise IdDoesNotExist("Required book doesn't exist")

    def sort_book_list (self):
        '''
        Sorts the list with respect to the book ids
        '''
        self.booksRepo.sort()

    def book_exists (self, ID):
        '''
        Checks if there is a book with given ID
        Input:
            ID - the required book id
        '''
        for i in self.booksRepo:
            if i.Id == ID:
                return True
        return False
    
    def search_book_Id (self, Id):
        '''
        Returns a list of all books that have the string Id book Id
        '''
        books = []
        for i in self.booksRepo:
            if Id.upper() in i.Id.upper():
                books.append(i)
        return books

    def search_book_author (self, author):
        '''
        Returns a list of all books that have the string author book author
        '''
        books = []
        for i in self.booksRepo:
            if author.upper() in i.author.upper():
                books.append(i)
        return books

    def search_book_title (self, title):
        '''
        Returns a list of all books that have the string title book title
        '''
        books = []
        for i in self.booksRepo:
            if title.upper() in i.title.upper():
                books.append(i)
        return books

    def most_rented_author (self, idDict):
        '''
         This provides the list of book authored, sorted in descending order of the number of rentals their books have
        '''
        authors = {}
        for i in idDict:
            index = self.booksRepo.find(i)
            book = self.booksRepo[index]

            if book.author not in authors:
                authors[book.author] = idDict[i]
            else:
                authors[book.author] += idDict[i]
        
        for i in self.booksRepo:
            if i.Id not in idDict:
                if i.author not in authors:
                    authors[i.author] = 0

        return authors

class ClientsService:
    def __init__ (self, clientsRepo, undoService = None):
        self.clientsRepo = clientsRepo
        self.undoService = undoService

    
    def add_client (self, client):
        '''
        Adds a client to the client list 
        Input:
            client - object of type Client
        '''
        if len(client.name) == 0:
            raise emptyString

        self.clientsRepo.store(client)

        undoOp = FunctionCall(self.remove_client, client.Id)
        redoOp = FunctionCall(self.add_client, client)
        operation = Operation(undoOp, redoOp)

        self.undoService.record(operation)

    
    def list_clients (self, clientList = None):
        '''
        Returns the list of some clients in a specific format
        Input:
            clientList - the list of some clients in a specific format (if no client list is given all clients are considered)
        Output:
            clients - the required clients in a specific format
        '''
        if clientList == None:
            clientList = self.clientsRepo
        clients = []
        count = 0
        for i in clientList:
            count += 1
            clients.append(str(count) + ". " + str(i))
        return clients

    def list_clients_Id (self, clientIds):
        '''
        Returns a list of client object type, given a list of their ids
        '''    
        clients = []
        for i in clientIds:
            index = self.clientsRepo.find(i)
            client = self.clientsRepo[index]
            clients.append(client)
        for i in self.clientsRepo:
            if i.Id not in clientIds:
                clients.append(i)
        
        return clients

    def remove_client (self,  ID):
        '''
        Removes a client with a given ID
        Input:
            ID - the id of the client to be removed
        '''
        self.clientsRepo.delete(ID)

    def update_client_name (self, ID, name):
        '''
        Updates the name of a client 
        Input:
            ID - the id of the client to be updated
            name - the new name
        '''
        self.clientsRepo.valid_ID(ID)
        if len(name) == 0:
            raise emptyString

        for i in self.clientsRepo:
            if int(i.Id) == int(ID):
                oldName = i.name
                i.name = name
                try:
                    self.clientsRepo.store_current_state()
                except: pass

                undoOp = FunctionCall(self.update_client_name, ID, oldName)
                redoOp = FunctionCall(self.update_client_name, ID, name)
                operation = Operation(undoOp, redoOp)

                self.undoService.record(operation)

                return
        raise IdDoesNotExist

    def sort_client_list (self):
        '''
        Sorts the client list with respect to client id
        '''
        self.clientsRepo.sort()

    
    def client_exists (self, ID):
        '''
        Checks if there is an client with given ID
        Input:
            ID - the required client id
        '''
        for i in self.clientsRepo:
            if i.Id == ID:
                return True
        return False

    def search_client_id (self, Id):
        '''
        Search for a client using partial string matching for id
        '''
        clients = []
        for i in self.clientsRepo:
            if Id.upper() in i.Id.upper():
                clients.append(i)
        return clients
    
    def search_client_name (self, name):
        '''
        Search for a client using partial string matching for name
        '''
        clients = []
        for i in self.clientsRepo:
            if name.upper() in i.name.upper():
                clients.append(i)
        return clients



class RentalsService:
    def __init__ (self, rentalsRepo, booksService, clientsService, undoService):
        self.rentalsRepo = rentalsRepo
        self.booksService = booksService
        self. clientsService = clientsService
        self.undoService = undoService
   
        

    def add_rental (self, rental):
        '''
        Adds a rental to the list of rentals
        Input:
            rental - object of type rental
        '''

        self.rentalsRepo.valid_ID(rental.Id)
        self.rentalsRepo.valid_ID(rental.bookId)
        self.rentalsRepo.valid_ID(rental.clientId)

        for i in self.rentalsRepo:
            if i.Id == rental.Id:
                raise duplicateID
            if i.bookId == rental.bookId:
                if i.returnedDate == None:
                    raise rentedBook
                elif i.returnedDate != None:
                    if rental.rentedDate <= i.returnedDate and rental.rentedDate >= i.rentedDate :
                        raise badDate
        
        if self.booksService.book_exists(rental.bookId) == False:
            raise bookDoesNotExist

        if self.clientsService.client_exists(rental.clientId) == False:
            raise clientDoesNotExist

        self.rentalsRepo.store(rental)

        undoOp = FunctionCall(self.remove_rental, rental.Id)
        redoOp = FunctionCall(self.add_rental, rental)
        operation = Operation(undoOp, redoOp)

        self.undoService.record(operation)

    def remove_rental (self, rentalId):
        self.rentalsRepo.delete(rentalId)

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
        self.rentalsRepo.valid_ID(ID)
        for i in self.rentalsRepo:
            if i.Id == ID:
                if i.returnedDate == None:
                    if i.rentedDate > date:
                        raise badDates
                    else:
                        for j in self.rentalsRepo:
                            if i.bookId == j.bookId and self.intersected_dates(i.rentedDate, date, j.rentedDate, j.returnedDate) ==False:
                                raise badReturnDate
                        oldDate = i.returnedDate
                        i.returnedDate = date

                        try:
                            self.rentalsRepo.store_current_state()
                        except: pass

                        undoOp = FunctionCall(self.set_return_date_none, i)
                        redoOp = FunctionCall(self.return_book, ID, date)

                        operation = Operation(undoOp, redoOp)

                        self.undoService.record(operation)

                        return
                else:
                    raise returnedBook
        raise rentalDoesNotExist

    def set_return_date_none(self, rental):
        rental.returnedDate = None
        try:
            self.rentalsRepo.store_current_state()
        except:pass

    def sort_rentals (self):
        '''
        Sorts the list of rentals with respect to rental id
        '''
        self.rentalsRepo.sort()
 
    def bookId_rentals (self, ID):
        '''
        Returns a list of rentals with a given book ID
        '''
        rentals = []
        for i in self.rentalsRepo:
            if i.bookId == ID:
                rentals.append(i)
        return rentals

    def clientId_rentals (self, ID):
        '''
        Returns a list of rentals with a given book ID
        '''
        rentals = []
        for i in self.rentalsRepo:
            if i.clientId == ID:
                rentals.append(i)
        return rentals

    def remove_rentals (self, rentals):
        '''
        Removes multiple rentals from a list of rentals
        '''
        for i in rentals:
            self.rentalsRepo.delete(i.Id)
    
    
    def add_rentals (self, rentals):
        '''
        Adds multiple rentals from a list of rentals
        '''
        for i in rentals:
            self.rentalsRepo.store(i)


    def most_rented_books (self):
        books = {}
        for i in self.rentalsRepo:
            if i.bookId not in books:
                books[i.bookId] = 1
            else:
                books[i.bookId] += 1
        
    
        return books

    def most_active_client (self):
        clients = {}
        for i in self.rentalsRepo:
            if i.clientId not in clients:
                if i.returnedDate != None:
                    clients[i.clientId] = (i.returnedDate - i.rentedDate).days
            else:
                if i.returnedDate != None:
                    clients[i.clientId] += (i.returnedDate - i.rentedDate).days
        
        clients = sorted(clients, key=clients.__getitem__, reverse = 1)

        return clients

    def remove_book_and_rentals (self, ID):
        book = self.booksService.search_book_Id(ID)[0]
        bookdIdRentals = self.bookId_rentals(ID)

        self.booksService.remove_bookID(ID)
        self.remove_rentals(bookdIdRentals)

        operationList = []

        f_undo = FunctionCall(self.booksService.add_book, book)
        f_redo = FunctionCall(self.booksService.remove_bookID, ID)
        operation = Operation(f_undo, f_redo)

        operationList.append(operation)

        f_undo = FunctionCall(self.add_rentals, bookdIdRentals)
        f_redo = FunctionCall(self.remove_rentals, bookdIdRentals)
        operation = Operation(f_undo, f_redo)

        operationList.append(operation)

        operations = Cascade(operationList)

        self.undoService.record(operations)

    def remove_client_and_rentals(self, ID):
        client = self.clientsService.search_client_id(ID)[0]
        clientIdRentals = self.clientId_rentals(ID)

        self.clientsService.remove_client(ID)
        self.remove_rentals(clientIdRentals)

        operationList = []

        f_undo = FunctionCall(self.clientsService.add_client, client)
        f_redo = FunctionCall(self.clientsService.remove_client, ID)
        operation = Operation(f_undo, f_redo)

        operationList.append(operation)

        f_undo = FunctionCall(self.add_rentals, clientIdRentals)
        f_redo = FunctionCall(self.remove_rentals, clientIdRentals)
        operation = Operation(f_undo, f_redo)

        operationList.append(operation)

        operations = Cascade(operationList)

        self.undoService.record(operations)


    def filter_key_id (self, l, r, obj):
        if obj.Id < l or obj.Id > r:
            return True
        return False

    def set_rentals (self, list):
        self.rentalsRepo.get_list = list


    def filter_rentals (self, l, r):
        self.rentalsRepo.valid_ID(l)
        self.rentalsRepo.valid_ID(r)

        oldRentals = self.rentalsRepo.get_list[:]

        filter(self.rentalsRepo.get_list, self.filter_key_id, l, r)

        newRentals = self.rentalsRepo.get_list[:]

        f_undo = FunctionCall(self.set_rentals, oldRentals)
        f_redo = FunctionCall(self.set_rentals, newRentals)
        operation = Operation(f_undo, f_redo)

        self.undoService.record(operation)



class FunctionCall:
    def __init__ (self, function, *parameters):
        self.function = function
        self.params = parameters
    
    def call (self):
        self.function(*self.params)
    

class Operation:
    def __init__ (self, undoFunction, redoFunction):
        self._undo = undoFunction
        self._redo = redoFunction

    def undo (self):
        self._undo.call()
    
    def redo (self):
        self._redo.call()

class Cascade:
    def __init__ (self, operationList):
        self.operations = operationList

    def undo (self):
        for i in self.operations:
            i.undo()
    
    def redo(self):
        for i in self.operations:
            i.redo()

class UndoService:
    def __init__ (self):
        self.history = []
        self.index = 0
        self.duringUndo = False

    def record (self, operation):
        if self.duringUndo == True:
            return 
        
        if self.index < len(self.history):
            self.history = self.history[:self.index]
        
        self.history.append(operation)
        self.index += 1
    
    def undo (self):
        if self.index == 0:
            raise noMoreUndos ("\nNo more undos are possible\n")

        self.duringUndo = True

        self.index -= 1
        self.history[self.index].undo()

        self.duringUndo = False
    
    def redo (self):
        if self.index == len(self.history):
            raise noMoreRedos ("\nNo more redos are possible\n")

        self.duringUndo = True

        self.history[self.index].redo()
        self.index += 1

        self.duringUndo = False

    def clear_history (self):
        self.history.clear()
        self.index = 0




