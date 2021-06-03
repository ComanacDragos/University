import torch
import torch.nn.functional as F
from settings import *
from torch import nn
import sys


class Unit(nn.Module):
    def __init__(self, in_channels, out_channels):
        super(Unit, self).__init__()

        self.conv = nn.Conv2d(in_channels=in_channels, kernel_size=3, out_channels=out_channels, stride=1, padding=1)
        self.bn = nn.BatchNorm2d(num_features=out_channels)
        self.activation = nn.ReLU()

    def forward(self, input):
        output = self.conv(input)
        output = self.bn(output)
        output = self.activation(output)
        return output


class Net(torch.nn.Module):
    def __init__(self):
        super(Net, self).__init__()

        self.net = nn.Sequential(
            self.unit(3, 32),
            self.unit(32, 32),
            self.maxPool(2),
            self.unit(32, 32),
            self.unit(32, 32),
            self.maxPool(2),
            self.unit(32, 32),
            self.unit(32, 32),
            self.maxPool(2),
            self.unit(32, 32),
            self.unit(32, 32),
            self.maxPool(2),
            self.unit(32, 64),
            self.unit(64, 64),
            self.maxPool(2),
            self.unit(64, 64),
            self.unit(64, 64),
            self.maxPool(2),
            self.unit(64, 128),
            self.unit(128, 128),
            self.avgPool(4)
        )
        self.fc = nn.Linear(in_features=128, out_features=1)

    @staticmethod
    def unit(in_channels, out_channels):
        return Unit(in_channels=in_channels, out_channels=out_channels)

    @staticmethod
    def avgPool(kernel_size):
        return nn.AvgPool2d(kernel_size=kernel_size)

    @staticmethod
    def maxPool(kernel_size):
        return nn.MaxPool2d(kernel_size=kernel_size)

    def forward(self, input):
        output = self.net(input)
        output = output.view(-1, 128)
        output = self.fc(output)
        output = torch.sigmoid(output)
        return output
