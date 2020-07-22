import unittest
from Obstruction.controller.game import *

class test_game(unittest.TestCase):
    def test_player_move(self):
        b = Board(3,3)
        ai = BetterAI(b)
        controller = Controller(b, "X", "O", ai)

        move = controller.player_move

        move(1,1)
        self.assertEqual(b.square(0, 0), 1)

        with self.assertRaises(BadMove):
            move(4,3)

        with self.assertRaises(BadMove):
            move(3,4)

        with self.assertRaises(BadMove):
            move(1,1)

        with self.assertRaises(BadMove):
            move(2,2)

        move(1,3)
        move(3,1)
        with self.assertRaises(GameOver):
            move(3, 3)

if __name__ == '__main__':
    unittest.main()
