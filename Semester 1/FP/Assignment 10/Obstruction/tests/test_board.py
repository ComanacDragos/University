import unittest
from Obstruction.domain.board import *

class test_board(unittest.TestCase):
    def test_create_board (self):
        b = Board(2,3)
        self.assertEqual(b.rows, 2)
        self.assertEqual(b.columns, 3)

    def test_move (self):
        b = Board(2,3)
        b.move(1,1,"X")
        b.move(0,0,"o")
        self.assertEqual(b.square(1,1), 1)
        self.assertEqual(b.square(0,0), -1)

    def test_square (self):
        b = Board(2,3)
        i = 0
        while i < b.rows:
            j = 0
            while j < b.columns:
                self.assertEqual(b.square(i,j), 0)
                j += 1
            i += 1

    def test_valid_move (self):
        b = Board(3,3)
        b.move(0, 0, "x")
        b.move(2, 0, "x")
        b.move(0, 2, "x")
        b.move(2, 2, "x")
        i = 0
        while i < b.rows:
            j = 0
            while j < b.columns:
                self.assertEqual(b.valid_move(i, j), False)
                j += 1
            i += 1

    def test_is_won (self):
        b = Board(3,3)
        b.move(0,0,"x")
        b.move(2, 0, "x")
        b.move(0, 2, "x")
        b.move(2, 2, "x")

        self.assertEqual(b.is_won(), True)

if __name__ == '__main__':
    unittest.main()
