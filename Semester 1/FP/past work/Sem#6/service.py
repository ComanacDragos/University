import random
from domain import *

class Game:

    def __init__ (self):
        self._pcNr = []
        while len(self._pcNr) < 4:
            nr = random.choice(range(10))
            if nr == 0 and len(self._pcNr) == 0:
                pass
            else:
                if nr not in self._pcNr:
                    self._pcNr.append(nr)
        self._pcNr = Guess(self._pcNr[0], self._pcNr[1], self._pcNr[2], self._pcNr[3])

        self._guesses = []

    def repeatedGuess (self, guess):
        if guess in self._guesses:
            return 1
        return 0

    def addGuess (self, guess):
        if self.repeatedGuess == 0:
            self._pcNr.append(guess)

    def nrBulls (self, guess):
        cont = 0
        '''
        if self._pcNr.One == guess.One:
            cont = cont + 1
        if self._pcNr.Two == guess.Two:
            cont = cont + 1
        if self._pcNr.Three == guess.Three:
            cont = cont + 1
        if self._pcNr.Four == guess.Four:
            cont = cont + 1
        '''

        l1 = self._pcNr.to_list()
        l2 = guess.to_list()

        for i,j in zip(l1,l2):
            if i == j:
                cont += 1
          
        return cont

    def nrCows (self, guess):
        cont = 0
        l1 = self._pcNr.to_list()
        l2 = guess.to_list()

        for i in l1:
            if i in l2:
                cont += 1
        return cont

    def validGuess (self, guess):
        try:
            g1 = int(guess.One)
            g1 = int(guess.Two)
            g1 = int(guess.Three)
            g1 = int(guess.Four)
        except:
            return 1
        else:
            if self.repeatedGuess(guess) == 1 :
                return 2
        return 0

    
    def winCond (self, guess):     
        valid = self.validGuess(guess)
        if valid == 1:
            return "Invalid guess"
        elif valid == 2:
            return "Game lost"
        elif valid == 0:
            if self.nrBulls == 4:
                return "Game won"


    def print_nr (self):
        print(self._pcNr)

    def createGuess (self, guess):
        try:
            guess = list(guess)
            guess = Guess(int(guess[0]), int(guess[1]), int(guess[2]), int(guess[3]))
        except:
            return 1
        else:
            return 0
            
'''
obj = Game()

obj.print_nr()
print(obj.nrBulls(Guess(1,2,3,4)))
print(obj.nrCows(Guess(1,2,3,4)))
'''
'''

1 generate 1000 numbers
2. for each generated numenr:
    number in [1023,9876]
    check no duplicate digits
'''