# classes 
# - how do they work in python?
# - which classes to write and how to turn them into a programs?
# test (classes), validation

# what is/are the domain entities

from math import sqrt

class Location:
    '''
    x,y,z - integers
    '''
    def __init__ (self, x,y,z):
        self._x = x
        self._y = y
        self._z = z
    
    #properties without setters are callerd read only
    @property
    def X (self):
        return self._x
    
    @property
    def Y (self):
        return self._y
    
    @property
    def Z (self):
        return self._z

    @X.setter
    def X (self, value):
        self._x = value

    @Y.setter
    def Y (self, value):
        self._y = value

    @Z.setter
    def Z (self, value):
        self._z = value

    def __sub__ (self, loc):
        return sqrt((self.X - loc.X)**2 + (self.Y - loc.Y)**2 + (self.Z - loc.Z)**2)

    def __str__ (self):
        return "(" + str(self.X) + "," + str(self.Y) + "," + str(self.Z) + ")"


def test_location():
    alderaan = Location(1,2,3) # function call operator
    
    assert alderaan.X == 1 and alderaan.Y == 2 and alderaan.Z == 3
    alderaan.X = 10
    assert alderaan.X == 10
    alderaan.Y +=5
    assert alderaan.Y == 7

    assert str(alderaan) == '(10,7,3)'
'''
    alderaan.get_x()

    # allows me to validate stars's position
    alderaan.set_x() # you run code so you can validate
    alderaan.set_x(alderaan.get_x() + 50) # ok but ugly
    # python properties to the resq!
    alderaan.X += 50 # code runs, so you can validate, and looks reasonable

 
    
    
    
    #lderaan._x = 5 # no code runs, so no validation is possible
'''
test_location()

class Star:
    '''
    location, mass, magnitude
    '''
    def __init__ (self, loc, mass, mag):
        self.Location = loc
        self. Mass = mass
        self. Magnitude = mag

    @property
    def Location (self):
        return self._loc

    @Location.setter
    def Location(self,value):
        self._loc = value

    @property
    def Mass (self):
        return self._mass

    @Mass.setter
    def Mass(self, value):
        if value < 0.1 or value > 50:
            raise ValueError("star must be in 0.1 50")
        self._mass = value

    @property
    def Magnitude (self):
        return self._mag

    @Magnitude.setter
    def Magnitude(self, value):
        if value < -1 or value > 15:
            raise ValueError("star magnitude be in -1 15")
        self._mag = value

