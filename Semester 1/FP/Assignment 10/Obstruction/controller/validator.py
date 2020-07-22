from Obstruction.domain.exceptions import *

class Validator:
    @staticmethod
    def natural_number (n):
        '''
        Checks if a given object is a natural number
        Input:
            - n - object
        Raises an exception if n is not a natural number
        '''
        errMsg = "The given input is not a natural number"

        try:
            n = float(n)
        except ValueError:
            raise BadMove(errMsg)
        else:
            if n < 0 or n != int(n):
                raise BadMove(errMsg)