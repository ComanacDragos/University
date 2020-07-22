class duplicateID (Exception):
    '''
    Duplicate bookId exception
    '''
    pass

class IdDoesNotExist (Exception):
    '''
    Required id does not exist
    '''
    pass

class badId (Exception):
    '''
    The book id is not a natural number
    '''
    pass

class emptyString (Exception):
    '''
    The string is empty
    '''
    pass

class bookDoesNotExist (Exception):
    '''
    The required book doesn't exist
    '''
    pass

class clientDoesNotExist (Exception):
    '''
    The required client doesn't exist
    '''
    pass

class rentalDoesNotExist(Exception):
    '''
    The required rental does not exist
    '''
    pass

class badDates (Exception):
    '''
    The rented date is bigger than the returned date
    '''
    pass

class rentedBook (Exception):
    '''
    The book is rented
    '''
    pass

class badDate (Exception):
    '''
    The given date is not a valid date
    '''
    pass

class returnedBook (Exception):
    '''
    The given book is returned 
    '''
    pass

class badReturnDate (Exception):
    '''
    The given return date is in a period in which the book was borrowed
    '''
    pass

class noMoreUndos (Exception):
    pass

class noMoreRedos (Exception):
    pass