from service import *
import unittest
import random

class test_repo_service (unittest.TestCase):
    def test_repo_valid_id (self):
        repo = Repository([])
        
        repo.valid_ID("4")
        
        with self.assertRaises(badId):
            repo.valid_ID("asd")
    
        with self.assertRaises(badId):
            repo.valid_ID("-3")
        
        with self.assertRaises(badId):
            repo.valid_ID("3.14")

    def test_repo_store (self):
        repo = Repository([Client("103", "name")])

        self.assertEqual("103", repo[0].Id)
        self.assertEqual("name", repo[0].name)

        cl1 = Client("102", "name2")

        repo.store(cl1)

        self.assertEqual(repo[-1].Id, "102")
        self.assertEqual(repo[-1].name, "name2")

        with self.assertRaises(duplicateID):
            repo.store(cl1)

    def test_repo_find (self):
        repo = Repository([Client("103", "name")])

        self.assertEqual(repo.find("103"), 0)

        with self.assertRaises(IdDoesNotExist):
            repo.find("1")
    
    def test_repo_delete (self):
        repo = Repository([Client("103", "name")])

        repo.delete("103")

        self.assertEqual(len(repo), 0)
        
        with self.assertRaises(IdDoesNotExist):
            repo.delete("103")

    def test_BooksService_add_book (self):
        service = BooksService(Repository([]), UndoService())

        book = Book("103", "titlu", "author")

        service.add_book(book)

        self.assertEqual(service.booksRepo[0], book)

        book = Book("104", "", "author")

        with self.assertRaises(emptyString):
            service.add_book(book)
        
        book = Book("105", "author", "")

        with self.assertRaises(emptyString):
            service.add_book(book)
        
    def test_BooksService_list_books (self):
        service = BooksService(Repository([Book("103", "title1", "author"), Book("104", "title2", "author")]))

        books = service.list_books()
        book1 = "1. " + str(Book("103", "title1", "author"))
        self.assertEqual(books[0], book1)
        book2 = "2. " + str(Book("104", "title2", "author"))
        self.assertEqual(books[1], book2)

    def test_BooksService_remove_bookId (self):
        service = BooksService(Repository([Book("103", "title1", "author"), Book("104", "title2", "author")]))        

        service.remove_bookID("103")

        self.assertEqual(service.booksRepo[0].Id, "104")

    def test_BooksService_update_book (self):
        service = BooksService(Repository([Book("103", "title1", "author"), Book("104", "title2", "author")]), UndoService())

        service.update_book_author("103", "asd103")
        service.update_book_title("104", "asd104")

        self.assertEqual(service.booksRepo[0].author, "asd103")
        self.assertEqual(service.booksRepo[1].title, "asd104")

        with self.assertRaises (emptyString):
            service.update_book_author("103", "")
        
        with self.assertRaises (IdDoesNotExist):
            service.update_book_author("105", "asd")
        
        with self.assertRaises (emptyString):
            service.update_book_title("103", "")
        
        with self.assertRaises (IdDoesNotExist):
            service.update_book_title("105", "asd")
        
    def test_ClientsService_add_client(self):
        service = ClientsService(Repository([Client("100", "name1"), Client("101", "name2")]), UndoService())

        cl1 = Client("102", "name3")

        service.add_client(cl1)

        self.assertEqual(service.clientsRepo[-1].Id, "102")
        self.assertEqual(service.clientsRepo[-1].name, "name3")

    def test_ClientsService_list_clients (self):
        service = ClientsService(Repository([Client("100", "name1"), Client("101", "name2")]))

        clients = service.list_clients()
        client1 = "1. " + str(Client("100", "name1"))
        self.assertEqual(clients[0], client1)
        client1 = "2. " + str(Client("101", "name2"))
        self.assertEqual(client1, clients[1])

    def test_ClientsService_remove_client (self):
        service = ClientsService(Repository([Client("100", "name1"), Client("101", "name2")]))

        service.remove_client("100")

        self.assertEqual(service.clientsRepo[-1].Id, "101")
        self.assertEqual(service.clientsRepo[-1].name, "name2")

    def test_ClientsService_update_client_name (self):
        service = ClientsService(Repository([Client("100", "name1"), Client("101", "name2")]), UndoService())

        service.update_client_name("101", "newName")

        self.assertEqual(service.clientsRepo[1].name, "newName")

    def test_Iterable (self):
        iterable = Iterable([1,2,3])
        iterable = iter(iterable)

        self.assertEqual(next(iterable), 1)
        self.assertEqual(next(iterable), 2)

        iterable[2] = 4
        self.assertEqual(next(iterable), 4)

        iterable.append(5)
        self.assertEqual(next(iterable), 5)

        with self.assertRaises(StopIteration):
            next(iterable)

        iterable[2] = 3
        del iterable[3]
        count = 1
        for i in iterable:
            self.assertEqual(i, count)
            count += 1

    def test_gnome_sort (self):
        for i in range(10):
            l = random.sample(range(0, 1000), 900)

            gnomeSort(l, lambda x,y: x<=y)
            i = 1
            while i < len(l)-1:
                self.assertLess(l[i-1], l[i])
                i += 1

    def test_filter (self):
        l = [1,2,3,4,453,234,234,234,5,12,43,400,6,7]
        filter(l, lambda l,r,obj: obj >= l and obj <= r, 8, 500)
        count = 1
        for i in l:
            self.assertEqual(i, count)
            count += 1



