# -*- coding: utf-8 -*-

import torch
import torch.nn.functional as F
from settings import *


class Net(torch.nn.Module):
    # the class for the network

    def __init__(self, n_feature=2, n_hidden=HIDDEN_LAYERS, hidden_size=HIDDEN_LAYER_SIZE, n_output=1):
        # we have two layers: a hidden one and an output one
        super(Net, self).__init__()
        self.hidden = torch.nn.ModuleList()
        self.hidden.append(torch.nn.Linear(n_feature, hidden_size))
        for _ in range(n_hidden - 1):
            self.hidden.append(torch.nn.Linear(hidden_size, hidden_size))

        self.output = torch.nn.Linear(hidden_size, n_output)

    def forward(self, x):
        # a function that implements the forward propagation of the signal
        # observe the relu function applied on the output of the hidden layer
        #x = F.relu(self.hidden(x))
        for layer in self.hidden:
            x = F.relu(layer(x))
        x = self.output(x)
        return x
