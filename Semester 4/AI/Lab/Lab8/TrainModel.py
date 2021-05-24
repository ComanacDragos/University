import time

from ImageClassifierDataset import ImageClassifierDataset
from Net import Net
from settings import *
import torch
import torch
import torch.nn as nn
from torchvision.datasets import CIFAR10
from torchvision.transforms import transforms
from torch.utils.data import DataLoader
from torch.optim import Adam, SGD
from torch.autograd import Variable
import numpy as np
from ImageClassifierDataset import ImageClassifierDataset
from Net import *
import time
import matplotlib.pyplot as plt


class TrainModel:
    def __init__(self):
        torch.cuda.empty_cache()
        self.learningRate = LEARNING_RATE
        db = ImageClassifierDataset()
        db.loadData()
        train_set, test_set = db.splitDataSet()
        self.trainSetSize = len(train_set)
        self.testSetSize = len(test_set)

        print(f"Train set: {self.trainSetSize} Test set: {self.testSetSize}")

        self.train_loader = DataLoader(train_set, batch_size=BATCH_SIZE, shuffle=True, num_workers=4, pin_memory=True)

        self.test_loader = DataLoader(test_set, batch_size=BATCH_SIZE, shuffle=False, num_workers=4, pin_memory=True)

        self.cuda_avail = torch.cuda.is_available()

        self.model = Net()

        print(f"Cuda: {self.cuda_avail}")
        if self.cuda_avail:
            self.model.cuda()

        self.optimizer = Adam(self.model.parameters(), lr=LEARNING_RATE)#, weight_decay=WEIGHT_DECAY)
        self.loss_fn = nn.BCELoss()

    def adjust_learning_rate(self, epoch):
        """if epoch > 180:
            self.learningRate /= 1000000
        elif epoch > 150:
            self.learningRate /= 100000
        elif epoch > 120:
            self.learningRate /= 10000
        elif epoch > 90:
            self.learningRate /= 1000
        elif epoch > 60:
            self.learningRate /= 100
        elif epoch > 30:
            self.learningRate /= 10"""
        for param_group in self.optimizer.param_groups:
            param_group["lr"] = self.learningRate * LEARNING_RATE_DECAY

    def save_models(self):
        torch.save(self.model.state_dict(), "weights/myModel.model")
        print("Checkpoint saved")

    def test(self):
        self.model.eval()
        test_acc = 0.0
        test_loss = 0.0
        for i, (images, labels) in enumerate(self.test_loader):

            if self.cuda_avail:
                images = Variable(images.cuda())
                labels = Variable(labels.cuda())

            outputs = self.model(images)
           # _, prediction = torch.max(outputs.data, 1)
            # prediction = prediction.cpu().numpy()
            prediction = torch.round(outputs.data)
            #print(outputs, labels, prediction)

            loss = self.loss_fn(outputs, labels)
            test_loss += loss.cpu().data.item() * images.size(0)
            test_acc += torch.sum(torch.eq(prediction, labels.data))

        test_acc /= self.testSetSize
        test_loss /= self.testSetSize

        return test_acc, test_loss

    def train(self):
        best_acc = 0.0
        best_loss = 1
        epochsSinceLastImprovement = 0
        losses = []
        print("Starting train...")
        for epoch in range(EPOCHS):
            startTime = time.time()
            self.model.train()
            train_acc = 0.0
            train_loss = 0.0
            for i, (images, labels) in enumerate(self.train_loader):
                if self.cuda_avail:
                    images = Variable(images.cuda())
                    labels = Variable(labels.cuda())

                self.optimizer.zero_grad()
                outputs = self.model(images)

                loss = self.loss_fn(outputs, labels)

                loss.backward()

                self.optimizer.step()

                train_loss += loss.cpu().data.item() * images.size(0)
                prediction = torch.round(outputs.data)
                train_acc += torch.sum(torch.eq(prediction, labels.data))

            self.adjust_learning_rate(epoch)

            train_acc /= self.trainSetSize
            train_loss /= self.trainSetSize

            test_acc, test_loss = self.test()

            if test_loss + LOSS_IMPROVEMENT < best_loss:
                if epoch != 0:
                    self.save_models()
                # best_acc = test_acc
                best_loss = test_loss
                epochsSinceLastImprovement = 0
            else:
                epochsSinceLastImprovement += 1

                if epochsSinceLastImprovement == EARLY_STOP:
                    print(
                        f"Epoch {epoch}, Train Accuracy: {train_acc} , TrainLoss: {train_loss} , Test Accuracy: {test_acc}, TestLoss: {test_loss} Time: {time.time() - startTime}")

                    print(f"No improvement in {epochsSinceLastImprovement} epochs, stopping...")
                    losses.append(test_loss)
                    break

            print(f"Epoch {epoch}, Train Accuracy: {train_acc} , TrainLoss: {train_loss} , Test Accuracy: {test_acc}, TestLoss: {test_loss} Time: {time.time() - startTime}")
            losses.append(test_loss)
        plt.plot(losses)
        plt.show()


if __name__ == '__main__':
    print("Starting...")
    TrainModel().train()
