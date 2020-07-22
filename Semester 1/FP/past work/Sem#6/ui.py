from service import *
import sys

class UI:
    def __init__ (self):
        self._game = Game()

    def readGuess (self):
        guess = input("Give guess: ")

        valid = self._game.validGuess()
        if valid == 1:
            print("Invalid guess")
        elif valid == 2:
            print("Game lost")
        elif valid == 0:
            guess = list(guess)
            self._game.addGuess(Guess(guess[0],guess[1], guess[2], guess[3]))
            self.printCowsBulls(guess)

    def printMenu (self):
        menu = '''
1. Start a new game
2. Exit
        '''
        print(menu)

    def printCowsBulls (self, guess):
        print("Cows: " + str(self._game.nrCows(guess)))
        print("Bulls: " + str(self._game.nrBulls(guess)))

    def start(self):
        print(self._game._pcNr)
        '''
        1. Print menu
            - Start new game
                - read user guess
                - self._game determines if repeated guess => game lost
                - self._game determines #bulls and #cows
        '''
        self.printMenu()
        choice = input(">")
        if choice == "1":
            while True:
                guess = input("Give guess: ")
                guess = list(guess)
                guess = Guess(int(guess[0]), int(guess[1]), int(guess[2]), int(guess[3]))
                self._game.addGuess(guess)
                winCond = self._game.winCond(guess)
                if winCond in ["Game won","Game lost"]:
                    print(winCond)
                    self.printMenu()
                    choice = input(">")
                    if choice == "2":
                        return
                elif winCond == "Invalid guess":
                    print(winCond)
                else:
                    print(self._game.nrBulls(guess))
                    print(self._game.nrCows(guess))
                    print(guess)
        else:
            return 


game = UI()

game.start()
