'''
tictactoe

player vs computer (player moves first)
validate everything
computer moves
    lvl1 always makes valid moves
    lvl2 takes all 1 move wins
    lvl3 prevent player's 1 move wins

'''
from texttable import  Texttable

class Board:
    def __init__(self):
        # empty square - 0
        # X - 1
        # 0 - -1
        self._data = [0] * 9
        self._moves = 0

    def get (self, x, y):
        # maybe transform X,O?
        return self._data[3*x +y]

    def isWon(self):
        #checks rows and columns
        for i in range(3):
            row = self._data[3*i:3*i+3]
            col = self._data[i:i+7:3]

            if abs(sum(row)) == 3 or abs (sum(col)) == 3:
                return True

        d = self._data
        if abs(d[0] + d[4] + d[8]) == 3:
            return True

        if abs(d[2]+ d[4] + d[6]) == 3:
            return True
        return False

    def isTie (self):
        #if 0 not in self_data
        return self.isWon() == False and self._moves == 9

    def move (self,x , y, symbol):
        # x,y in [0, 1, 2], symbol in [x,O]
        if x not in [0, 1, 2] or y not in [0, 1, 2]:
            raise ValueError("Move not inside the board")

        if self._data[3*x+y] != 0:
            raise ValueError("Square is already taken")

        if symbol not in ['X', 'O']:
            raise ValueError("Bad symbol!")

        d = {'X':1, 'O':-1}
        self._data[3*x+y] = d[symbol]

        self._moves += 1



    def __str__ (self):
        t = Texttable()
        d = {-1: 'O', 0: ' ', 1: 'X'}

        for i in range(0, 8, 3):
            row = self._data[i:i+3]
            for j in range(3):
                row[j] = d[row[j]]
            t.add_row(row)

        return t.draw()


# decide the computer's next move
class SimpletonComputer: # a kind of computer player
    def calculateMove (self, board):
        # return (x,y) for computer move
        for i in range(3):
            for j in range(3):
                if board.get(i,j) == 0:
                    return (i,j)
        raise ValueError("Board is full!")

import random

class RandomMoveComputer:
    def calculateMove (self, board):
        # return (x,y) for computer move
        candidates = []
        for i in range(3):
            for j in range(3):
                if board.get(i,j) == 0:
                    candidates.append((i,j))
        return random.choice(candidates)
        raise ValueError("Board is full!")

class SmarterComputer:
    def __init__(self, randomMoveComputer):
        #...
        pass
    def calcultateMove (self, board):
        pass
    #1. can i win the game
    #yes do it
    #no - call randomMoveComputer.calculateMove(board


class Game:  # a kind of controller/service
    def __init__(self, board, computerPlayer):
        self._board = board
        self._computerPlayer = computerPlayer

    def getBoard (self):
        return self._board


    def playerMove (self, x, y):
        self._board.move(x, y, 'X')

    def computerMove (self):
        move = self._computerPlayer.calculateMove(self._board)
        #computer must generate valid moves only
        # this should raise no error
        self._board.move(move[0], move[1], 'O')


class UI:
    def __init__(self, game):
        self._game = game

    def _readPlayerMove (self):
        # >1 2
        # Return the (x,y) tuple that reprezents the player's move
        while True:
            try:
                cmd = input(">").split(" ")
                return (int(cmd[0]), int(cmd[1]))
            except Exception:
                print("Invalid coordinates!")

    def start(self):
        b = self._game.getBoard()

        playerMove = True
        while b.isWon() == False and b.isTie() == False:
            #while cond must be checked after each move
            print(b)
            if playerMove == True:
                try:
                    move = self._readPlayerMove()
                    self._game.playerMove(move[0], move[1])
                except Exception as e:
                    print(e)
                    continue
            else:
                self._game.computerMove()
            playerMove = not playerMove

        print(b)
        # win/lost message
        if b.isTie():
            print("It's a draw!")
        else:
            #game was won
            if playerMove == False:
                print("Congrats!")
            else:
                print("You were defeated!")



b = Board()
# computer uses the strategy design pattern
#ai = SimpletonComputer()
ai = RandomMoveComputer()
g = Game(b, ai)
ui = UI(g)
ui.start()