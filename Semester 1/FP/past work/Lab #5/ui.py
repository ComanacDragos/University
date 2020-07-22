from service import *

class UI:

    def __init__ (self):
        self.service = Service()
    
    @staticmethod
    def print_menu ():
        menu = '''
1. Add a new book
2. Show list of books
3. Filter books
4. Undo
5. Exit
        '''
        print(menu)

    def error_messages (self, errorKey):
        errorMessages = {
            "1" : "Invalid book number",
            "2" : "Invalid author",
            "3" : "Invalid title",
            "4" : "Duplicate book number",
            "5" : "There are no books where the title starts with the given word",
            "6" : "The list of books is in it's initial state",
            "7" : "Must use only one word",
            "8" : "The list of books is empty"
        }
        print("\n" + errorMessages[str(errorKey)] + "\n")


    def ui_add_book (self):
        '''
        UI function - reads the characteristic of a book then adds it to the list of books
        '''
        print("")
        isbn = input("Give isbn: ")
        author = input("Give author: ")
        title = input("Give title: ")
        print("")
        isbn = isbn.strip()
        title = title.strip()
        book = Book(isbn, author, title)

        succes = self.service.addBook(book)

        if succes == 0:
            print("The book was added succesfully")
        else:
            self.error_messages(succes)

    def ui_list_books (self):
        '''
        UI function for printing the list of books
        '''
        succes = self.service.valid_list()
        if succes != 0:
            self.error_messages(succes)
        else:
            print("")
            for i in self.service.list_books():
                print (i)

    def ui_filter_books (self):
        '''
        UI function that removes word star
        '''
        print("")
        filterWord = input ("Give filter word: ")
        print("")

        succes = self.service.filter(filterWord)

        if succes == 0:
            print("The required books were removed")
        else:
            self.error_messages(succes)

    def ui_undo (self):
        succes = self.service.undo()
        if succes != 0:
            self.error_messages(succes)
        else:
            print ("\nThe undo was succesfull\n")


    def start (self):
        commands = {
            "1" : self.ui_add_book,
            "2" : self.ui_list_books,
            "3" : self.ui_filter_books,
            "4" : self.ui_undo,
            "6" : self.service.print_history
        }
        self.service._history = []
        while True :
            self.print_menu()
            cmd = input(">>")
            if cmd in commands:
                commands[cmd]()
            elif cmd == "5":
                return
            else:
                print("\nInvalid command\n")

ui = UI()
ui.start()