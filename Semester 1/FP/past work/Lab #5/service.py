from domain import Book
import copy

class Service :
    
    def __init__ (self):
        self._books = []
        self._history = []
        self.addBook(Book("100", "Mircea Eliade", "Nunta in cer"))
        self.addBook(Book("101", "Gabriel García Márquez", "Un veac de singuratate"))
        self.addBook(Book("102", "Alexandre Dumas", "Dama cu camelii"))
        self.addBook(Book("103", "James Clavell", "Shogun"))
        self.addBook(Book("104", "Lesley Downer", "Puntea viselor"))
        self.addBook(Book("105", "Karl May", "Winnetou"))
        self.addBook(Book("106", "Emil cioran", "Tratat de descompunere"))
        self.addBook(Book("107", "Gabriel Liiceanu", "Nebunia de a gandi cu mintea ta"))
        self.addBook(Book("108", "Mircea Eliade", "Noaptea de sanziene"))
        self.addBook(Book("109", "Paulo Coelho", "Jurnalul unui mag"))
        

    def valid_add (self, book):
        '''
        Checks if the book that is added to the list is valid
        Input parameters:
            book - object of type Book
        Output parameters:
            0 - if the book is valid
            a error key otherwise - natural number
        '''
        if type(book.isbn) != str:
            return 1
        if type(book.author) != str:
            return 2
        if type(book.title) != str:
            return 3

        

        for i in self._books:
            if book.isbn == i.isbn:
                return 4
        
        return 0
    
    def addBook (self, book):
        '''
        Adds a book to the list of books
        Input parameters:
            book - object of class Book
        Output:
            0 if the book was added succesfully
            an error key otherwise - natural number
        '''
        valid = self.valid_add(book)
        if valid == 0:
            self.add_to_history()
            self._books.append(book)
            return 0
        else:
            return valid

    def valid_list (self):
        '''
        Checks if the list of books is empty
        Output:
            0 if the list if the list if not empty
            8 if the list is empty
        '''
        if len(self._books) == 0:
            return 8
        else:
             return 0

    def list_books (self):
        '''
        Creates a list of all books and it returns it 
        Output paramtetrs:
            bookList - the list of books
        '''
        count = 0
        bookList = []
        if len (self._books) == 0:
            return "There are no books in the list"
        else:
            for i in self._books:
                count += 1
                bookList.append(str(count) + ". " + str(i))
        return bookList
            
    def valid_filter (self, word):
        '''
        Checks if the filter word is made of only one word
        Input parameters:
            word - the filter word
        Output parameters:
            0 if the filter word is made up of only one word
            7  if not
        '''
        idx = word.find(" ")
        if idx == -1:
            return 0
        else:
             return 7

    def filter (self, word):
        '''
        Removes all books starting with a given word
        Input parameters:
            word - the given word
        Output:
            0 if the filter was succesful
            a error key otherwise
        '''
        if len(self._books) == 0:
            return 8

        valid = self.valid_filter(word)

        if valid != 0:
            return valid
        else:
            ok = 0
            cont = 0
            n = len(self._books)
            toBeRemoved = []
            while cont < n:
                i = self._books[cont]
                idx = i.title.find(" ")
                if idx != -1:
                    firstWord = i.title[:idx]
                else:
                    firstWord = i.title
                if word == firstWord:
                    toBeRemoved.append(i)
                    ok = 1
                cont += 1

            if ok == 0:
                return 5
            else:
                self.add_to_history()
                for i in toBeRemoved:
                    self._books.remove(i)
                return 0

    def add_to_history (self):
        '''
        Adds to history the current list of books
        '''
        if len(self._history) != 0:
            if self._books == self._history[-1]:
                return
            else:
                newBooks = copy.deepcopy(self._books)
                self._history.append(newBooks)
        else:
            newBooks = copy.deepcopy(self._books)
            self._history.append(newBooks)

    def valid_undo (self):
        '''
        Checks if the undo is relevant
        Output:
            0 if the undo is relevant
            8 if the current list of books is the same as the last list of books
            6 if the list is in it's initial state
        '''
        if len(self._history) == 0:
            return 6
        
        return 0
        
    def undo (self):
        '''
        Undoes the last operation that changes the list of books
        Output:
            0 if the undo was succesfull
            an error key otherwise - natural number
        '''
        valid = self.valid_undo()
        if valid != 0:
            return valid
        else:
            self._books.clear()
            self._books = copy.deepcopy(self._history[-1])
            '''
            for i in aux:
                self._books.append(i)
            '''
            self._history.remove(self._history[-1])
            
            return 0
        
        

    def print_history (self):
        for i in self._history:
            for j in i:
                print(j)
            print("")
        
def test_add_book():
    service = Service ()
    book = Book("1", "author", "title")
    assert service.valid_add(book) == 0
    book = Book([1,2], "asd", "asd")
    assert service.valid_add(book) == 1

    book = Book("asd", [1,2], "asd")
    assert service.valid_add(book) == 2

    book = Book("asd", "asd", [1,2])
    assert service.valid_add(book) == 3

    book = Book("1", "author", "title")
    book = Book("1", "autr", "title")
    service.addBook(book)
    assert service.valid_add(book) == 4

test_add_book()
 