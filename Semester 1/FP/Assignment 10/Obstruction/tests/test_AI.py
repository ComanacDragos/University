import unittest
from Obstruction.controller.computerAI import *

class test_AI(unittest.TestCase):
    def test_generate_move(self):
        b = Board(3, 3)
        ai = EasyAI(b)

        b.move(0, 0, "X")
        self.assertEqual(ai.generate_move(), (0,2))
        b.move(0,2, "O")
        self.assertEqual(ai.generate_move(), (2,0))

    def test_better_ai_winning_move (self):
        board = Board(3,3)
        ai = BetterAI(board)
        self.assertEqual(ai.winning_move(), (1,1))

    def test_better_ai_valid_neighbors (self):
        board = Board(3,3)
        ai = BetterAI(board)
        self.assertEqual(ai.valid_neighbors(1,1), 8)

        board.move(0, 0, "X")
        self.assertEqual(ai.valid_neighbors(2, 2), 2)

    def test_better_ai_most_valid_neighbors(self):
        board = Board(3,3)
        ai = BetterAI(board)
        self.assertEqual(ai.most_valid_neighbors(), [1,1])

        board.move(0, 0, "x")
        self.assertEqual(ai.most_valid_neighbors(), [1,2])

        board.move(0,2,"x")
        board.move(2,0,"x")
        self.assertEqual(ai.most_valid_neighbors(), [2,2])

    def test_better_ai_generate_move (self):
        board = Board(3,3)
        ai = BetterAI(board)
        self.assertEqual(ai.generate_move(), [1,1])
        board.move(0,0, "x")
        self.assertEqual(ai.generate_move(), [1,2])

if __name__ == '__main__':
    unittest.main()
