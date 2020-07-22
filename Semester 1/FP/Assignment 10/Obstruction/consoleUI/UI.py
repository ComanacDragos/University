from Obstruction.controller.game import *
class UI:
    def __init__(self):
        self.first()
        self.init_board_size()
        self._board = Board(self.rows, self.col)
        self.difficulty()
        self._controller = Controller(self._board, self.player, self.computer, self.ai)


    def first (self):
        while True:
            choice = input("Do you want to go first? (1/0): ").strip()
            if choice == "1":
                self.player = "X"
                self.computer = "O"
                self.first = 1
                return
            elif choice == "0":
                self.player = "O"
                self.computer = "X"
                self.first = -1
                return
            else:
                print("\nInvalid command\n")

    def init_board_size (self):
        ok = 0
        while ok == 0:
            try:
                try:
                    self.rows = float(input("Give number of rows: ").strip())
                except ValueError:
                    raise ValueError("Number of rows is not a natural number different from 0")
                if self.rows < 1 or int(self.rows) != self.rows:
                    raise ValueError("Number of rows is not a natural number different from 0")

                try:
                    self.col = float(input("Give number of columns: ").strip())
                except ValueError:
                    raise ValueError("Number of columns is not a natural number different from 0")
                if self.col < 1 or int(self.col) != self.col:
                    raise ValueError("Number of columns is not a natural number different from 0")

            except ValueError as err:
                print("\n" + str(err) + "\n")
            else:
                ok = 1

    def difficulty (self):
        #self.ai = EasyAI(self._board)
        self.ai = BetterAI(self._board)

    def ui_player_move (self):
        x = input("Give row number: ").strip()
        y = input("Give column numner: ").strip()
        self._controller.player_move(x, y)

    def ui_computer_move (self):
        self._controller.computer_move()

    def ui_start_console (self):
        if self.player == "O":
            try:
                self.ui_computer_move()
            except GameOver as err:
                print(self._controller.get_board())
                print(err)
                return

        while True:
            try:
                #if self.player == "X":
                print(self._controller.get_board())
                self.ui_player_move()
                self.ui_computer_move()
            except BadMove as err:
                print(err)
            except GameOver as err:
                print(self._controller.get_board())
                print(err)
                return
