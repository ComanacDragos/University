import pygame
from random import random
import numpy as np
from Domain.settings import *


class Map:
    def __init__(self, n=HEIGHT, m=WIDTH):
        self.n = n
        self.m = m
        self.surface = np.zeros((self.n, self.m))

    def randomMap(self, fill=FILL_FACTOR):
        for i in range(self.n):
            for j in range(self.m):
                if random() <= fill:
                    self.surface[i][j] = WALL

    def __str__(self):
        string = ""
        for i in range(self.n):
            for j in range(self.m):
                string += str(int(self.surface[i][j]))
            string += "\n"
        return string

    def image(self, colour=BLUE, background=WHITE):
        imagine = pygame.Surface((SQUARE_WIDTH * WIDTH, SQUARE_HEIGHT * HEIGHT))
        brick = pygame.Surface((SQUARE_WIDTH, SQUARE_HEIGHT))
        brick.fill(colour)
        imagine.fill(background)
        for i in range(self.n):
            for j in range(self.m):
                if self.surface[i][j] == 1:
                    imagine.blit(brick, (j * SQUARE_WIDTH, i * SQUARE_HEIGHT))

        return imagine

    def __getitem__(self, position):
        return self.surface[position[0]][position[1]]
