from texttable import Texttable
from Obstruction.domain.exceptions import *

class Board:
    def __init__(self, rows, columns):
        self._rows = int(rows)
        self._columns = int(columns)

        self._board = []
        for i in range(self._rows):
            row = []
            for j in range(self._columns):
                row.append(0)
            self._board.append(row)

    @property
    def rows (self):
        return self._rows

    @property
    def columns (self):
        return self._columns

    def __str__(self):
        symbols  = {
            0: " ",
            1: "X",
            -1: "O"
        }
        t = Texttable()
        for i in range(self.rows):
            l = self._board[i][:]
            for j in range(self.columns):
                l[j] = symbols[l[j]]
            t.add_row(l)

        return t.draw()

    def __getitem__(self, item):
        return self._board[item]

    def move (self, row, col, symbol):
        '''
        Function puts an X or an O at the  (x,y) coordinates of the board matrix
        :param row: the x coordinate
        :param col: y coordinate
        :param symbol: X or O
        :return: None
        '''
        symbols = {
            "X": 1,
            "O":-1
        }
        self._board[row][col] = symbols[symbol.upper()]

    def square (self, row, col):
        '''
        Returns the square at a given position
        :param row: The row where the square is
        :param col: The column where the square is
        :return: 0, 1 or -1
        '''
        return self._board[row][col]

    def valid_move (self, row, col):
        '''
        Cheks if for a given square all the neighbours are free
        :param row: the row
        :param col: the column
        :return: True if all the neighbours are free, False otherwise
        '''

        if row >= self.rows or col>= self.columns or row < 0 or col < 0:
            return False

        if self.square (row, col) != 0:
            return False

        try:
            if self.square(row+1, col) != 0:
                return False
        except:
            pass

        try:
            if self.square(row, col+1) != 0:
                return False
        except:
            pass

        try:
            if row < 1:
                raise ValueError
            if self.square(row-1, col) != 0:
                return False
        except:
            pass

        try:
            if col < 1:
                raise ValueError
            if self.square(row, col-1) != 0:
                return False
        except:
            pass

        try:
            if row < 1 or col < 1:
                raise ValueError
            if self.square(row-1, col-1) != 0:
                return False
        except:
            pass

        try:
            if self.square(row+1, col+1) != 0:
                return False
        except:
            pass

        try:
            if col < 1:
                raise ValueError
            if self.square(row+1, col-1) != 0:
                return False
        except:
            pass

        try:
            if row < 1:
                raise ValueError
            if self.square(row-1, col+1) != 0:
                return False
        except:
            pass
        return True

    def is_won (self):
        '''
        Checks if the game is won
        :return: True if it is / False otherwise
        '''
        i = 0
        while i < self.rows:
            j = 0
            while j < self.columns:
                if self.valid_move(i,j) == True:
                    return False
                j += 1
            i += 1
        return True
