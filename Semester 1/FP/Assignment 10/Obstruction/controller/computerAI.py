from Obstruction.domain.board import *
from copy import *

class EasyAI:
    def __init__(self, board):
        self._board = board

    def generate_move (self):
        '''
        Returns the first free square of the board
        :return: the tupple (i,j) where i is the row of the free square and j is the column
        '''
        i = 0
        while i < self._board.rows:
            j = 0
            while j < self._board.columns:
                if self._board.valid_move(i, j):
                    return (i,j)
                j += 1
            i += 1

class BetterAI:
    def __init__(self, board):
        self._board = board

    def winning_move (self):
        '''
        Returns a winning move if it exists, False otherwise
        '''
        i = 0
        while i < self._board.rows:
            j = 0
            while j < self._board.columns:
                aux = deepcopy(self._board)
                if aux.valid_move(i, j) == True:
                    aux.move(i, j, "O")
                    if aux.is_won() == True:
                        return [i,j]
                j += 1
            i += 1
        return False

    def valid_neighbors (self, row, col):
        '''
        Returns the number of valid neighbors of a given square
        :param row: row number
        :param col: column number
        :return: number of valid neighbors
        '''
        count = 0
        b = self._board
        if b.valid_move(row+1, col) == True:
            count += 1
        if b.valid_move(row, col+1) == True:
            count += 1
        if b.valid_move(row-1, col) == True:
            count += 1
        if b.valid_move(row, col-1) == True:
            count += 1
        if b.valid_move(row+1, col+1) == True:
            count += 1
        if b.valid_move(row-1, col-1) == True:
            count += 1
        if b.valid_move(row+1, col-1) == True:
            count += 1
        if b.valid_move(row-1, col+1) == True:
            count += 1

        return count

    def most_valid_neighbors (self):
        '''
        Returns the square with the highest number of valid squares
        :return: returns a list with 2 elements: the row and column of the required square
        '''
        maxSquare = [-1, -1]
        max = -1

        i = 0
        while i < self._board.rows:
            j = 0
            while j < self._board.columns:
                if self._board.valid_move(i, j) == True:
                    neighbors = self.valid_neighbors(i, j)
                    if max < neighbors:
                        max = neighbors
                        maxSquare[0] = i
                        maxSquare[1] = j
                j += 1
            i += 1
        return maxSquare

    def generate_move (self):
        '''
        Returns a move
        '''
        if self.winning_move() != False:
            return self.winning_move()

        return self.most_valid_neighbors()

