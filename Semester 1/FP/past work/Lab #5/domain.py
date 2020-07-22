class Book:

    def __init__ (self, bn, aut, titl):
        '''
        Input parameters:
            isbn, author, title - strings
        '''
        self.isbn = bn
        self._aut = aut
        self._titl = titl
    
    @property
    def isbn (self):
        return self._bn

    @property
    def author (self):
        return self._aut

    @property
    def title (self):
        return self._titl

    @isbn.setter
    def isbn (self, value):
        self._bn = value
    
    @author.setter
    def author (self, value):
        self._aut = value

    @title.setter
    def title (self, value):
        self._title = value

    def __str__ (self):
        return "The book number is " + self.isbn + ", the author is " + self.author + " and the title is " + self.title

    def __eq__(self,value):
        return self.isbn == value.isbn and self.author == value.author and self.title == value.title
        
def test_book ():
    book = Book ("1","Eliae", "Nunta in cer")
    assert book.author == "Eliae"
    assert book.isbn == "1"
    assert book.title == "Nunta in cer"
    assert book.isbn != 1
test_book()