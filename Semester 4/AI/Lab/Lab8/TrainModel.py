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
from torch.optim import Adam
from torch.autograd import Variable
import numpy as np
from ImageClassifierDataset import ImageClassifierDataset
from Net import *
import time


class TrainModel:
    def __init__(self):
        """self.train_transformations = transforms.Compose([
            transforms.RandomHorizontalFlip(),
            transforms.RandomCrop(32, padding=4),
            transforms.ToTensor(),
            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
        ])"""
        self.learningRate = LEARNING_RATE
        db = ImageClassifierDataset()
        db.loadData()
        train_set, test_set = db.splitDataSet()
        self.trainSetSize = len(train_set)
        self.testSetSize = len(test_set)

        print(f"Train set: {self.trainSetSize} Test set: {self.testSetSize}")

        self.train_loader = DataLoader(train_set, batch_size=BATCH_SIZE, shuffle=True, num_workers=4)

        """self.test_transformations = transforms.Compose([
            transforms.ToTensor(),
            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
        ])"""

        self.test_loader = DataLoader(test_set, batch_size=BATCH_SIZE, shuffle=False, num_workers=4)

        self.cuda_avail = torch.cuda.is_available()

        self.model = Net()

        print(f"Cuda: {self.cuda_avail}")
        if self.cuda_avail:
            self.model.cuda()

        self.optimizer = Adam(self.model.parameters(), lr=LEARNING_RATE, weight_decay=WEIGHT_DECAY)
        self.loss_fn = nn.CrossEntropyLoss()

    def adjust_learning_rate(self, epoch):
        if epoch > 180:
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
            self.learningRate /= 10

        for param_group in self.optimizer.param_groups:
            param_group["lr"] = self.learningRate

    def save_models(self):
        torch.save(self.model.state_dict(), "weights/myModel.model")
        print("Checkpoint saved")

    def test(self):
        self.model.eval()
        test_acc = 0.0
        for i, (images, labels) in enumerate(self.test_loader):

            if self.cuda_avail:
                images = Variable(images.cuda())
                labels = Variable(labels.cuda())

            # Predict classes using images_faces from the test set
            outputs = self.model(images)
            _, prediction = torch.max(outputs.data, 1)
            # prediction = prediction.cpu().numpy()

            test_acc += torch.sum(torch.eq(prediction, labels.data))

        # Compute the average acc and loss over all 10000 test images_faces
        test_acc /= self.testSetSize

        return test_acc

    def train(self):
        best_acc = 0.0
        epochsSinceLastImprovement = 0
        for epoch in range(EPOCHS):
            startTime = time.time()
            self.model.train()
            train_acc = 0.0
            train_loss = 0.0
            for i, (images, labels) in enumerate(self.train_loader):
                # Move images_faces and labels to gpu if available
                if self.cuda_avail:
                    images = Variable(images.cuda())
                    labels = Variable(labels.cuda())

                # Clear all accumulated gradients
                self.optimizer.zero_grad()
                # Predict classes using images_faces from the test set
                outputs = self.model(images)
                # Compute the loss based on the predictions and actual labels
                loss = self.loss_fn(outputs, labels)
                # Backpropagate the loss
                loss.backward()

                # Adjust parameters according to the computed gradients
                self.optimizer.step()

                train_loss += loss.cpu().data.item() * images.size(0)
                _, prediction = torch.max(outputs.data, 1)

                train_acc += torch.sum(torch.eq(prediction, labels.data))

            # Call the learning rate adjustment function
            self.adjust_learning_rate(epoch)

            # Compute the average acc and loss over all 50000 training images_faces
            train_acc /= self.trainSetSize
            train_loss /= self.trainSetSize

            # Evaluate on the test set
            test_acc = self.test()

            # Save the model if the test acc is greater than our current best
            if test_acc > best_acc + LOSS_IMPROVEMENT:
                if epoch != 0:
                    self.save_models()
                best_acc = test_acc
                epochsSinceLastImprovement = 0
            else:
                epochsSinceLastImprovement += 1

                if epochsSinceLastImprovement == EARLY_STOP:
                    print(f"No improvement in {epochsSinceLastImprovement} epochs, stopping...")
                    return


            # Print the metrics
            print(f"Epoch {epoch}, Train Accuracy: {train_acc} , TrainLoss: {train_loss} , Test Accuracy: {test_acc}, Time: {time.time() - startTime}")


if __name__ == '__main__':
    print("Starting...")
    TrainModel().train()
