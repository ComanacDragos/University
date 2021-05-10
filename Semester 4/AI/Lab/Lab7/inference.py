# -*- coding: utf-8 -*-
"""
Created on Tue Apr 27 14:20:51 2021

@author: tudor
"""

import torch
import torch.nn.functional as F
from utils import sinFunction
import numpy as np
import matplotlib.pyplot as plt
import time
from trainModel import TrainModel

import myModel


# we load the model

# visualise the parameters for the ann (aka weights and biases)
# for name, param in ann.named_parameters():
#     if param.requires_grad:
#         print (name, param.data)


class UI:
    def __init__(self, filePath="myNet.pt"):
        self._filePath = filePath
        self.ann = myModel.Net()

        # self.ann.load_state_dict(torch.load(filePath))
        # self.ann.eval()

        self.commands = {
            '1': (self.visualizeParameters, 'Visualize parameters'),
            '2': (self.inputValues, 'Input values'),
            '3': (self.plot, 'Plot values'),
            '4': (self.train, 'Train'),
            '5': (self.loadAnn, 'Load ann')
        }

    def visualizeParameters(self):
        for name, param in self.ann.named_parameters():
            if param.requires_grad:
                print(name, param.data)

    def train(self):
        start = time.time()
        train = TrainModel()
        print(f"Time to load: {time.time() - start}")
        start = time.time()
        train.train()
        print(f"Time to train: {time.time() - start}")
        self.ann = train.ann
        plt.plot(train.averages)
        plt.show()

    def loadAnn(self):
        self.ann = myModel.Net()

        self.ann.load_state_dict(torch.load(self._filePath))
        self.ann.eval()

    def inputValues(self):
        while True:
            x = input("x = ")
            if x == 'x':
                return
            y = input("y = ")
            if y == 'x':
                return

            x, y = torch.tensor(float(x)), torch.tensor(float(y))
            print(f"Computed Value: {self.ann(torch.tensor([x, y])).tolist()[0]}")
            print(f"Actual value: {sinFunction(x, y)}\n")

    def plot(self):
        points = set()
        size = int(input("Size: "))
        while len(points) != size:
            points.add(
                tuple(np.random.uniform(-10, 10, 2))
            )
        fig = plt.figure()
        ax = plt.axes(projection='3d')

        prediction = self.ann(torch.tensor(torch.tensor([(float(x), float(y)) for x, y in points]))).detach().numpy()

        x, y, z, zTrue = [], [], prediction, []
        for xCoord, yCoord in points:
            x.append(xCoord)
            y.append(yCoord)
            zTrue.append(sinFunction(torch.tensor(xCoord), torch.tensor(yCoord)).numpy())
        ax.scatter(x, y, zTrue, color='red')
        ax.scatter(x, y, z, color='blue')
        plt.show()

    def printMenu(self):
        for key, (_, text) in self.commands.items():
            print(f"{key}. {text}")

    def start(self):
        while True:
            self.printMenu()
            command = input(">> ")
            if command == 'x':
                return
            if command in self.commands:
                self.commands[command][0]()
            else:
                print('Bad command')
            print()


UI().start()
