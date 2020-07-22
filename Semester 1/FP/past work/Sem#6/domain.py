class Guess ():
    def __init__ (self, one, two, three, four):
        self._guess = []
        self._guess.append(one)
        self._guess.append(two)
        self._guess.append(three)
        self._guess.append(four)

    @property
    def One (self):
        return self._guess[0]

    @property
    def Two (self):
        return self._guess[1]
    
    @property
    def Three (self):
        return self._guess[2]
    
    @property
    def Four (self):
        return self._guess[3]

    def __str__ (self):
        return str(self.One) + str(self.Two) + str(self.Three) + str(self.Four)

    def __eq__ (self, guess):
        return self.One == guess.One and self.Two == guess.Two and self.Three == guess.Three and self.Four == guess.Four

    def to_list (self):
        l = []
        l.append(self.One)
        l.append(self.Two)
        l.append(self.Three)
        l.append(self.Four)
        return l

obj = Guess(1,2,3,4)
obj2 = Guess(1,2,3,4)

