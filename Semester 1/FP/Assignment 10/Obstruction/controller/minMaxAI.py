from Obstruction.domain.board import *

class Node:
    def __init__(self, number, board):
        self._nr = number
        self._board = board
        self._succesors = []


    @property
    def nr (self):
        return self._nr

    @property
    def board (self):
        return self._board


class Graph:
    def __init__(self):
        self.graph = []


first = Node(3,Board(3,3))
