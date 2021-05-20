import torch
import torch.nn as nn
import torch.optim as optim
import time
from torch.utils.data import Dataset, DataLoader
from torchvision import datasets, models, transforms
import os
from settings import *
from PIL import Image
import numpy as np
import random


class ImageClassifierDataset(Dataset):
    def __init__(self, class_to_label=None):
        self.images = []
        self.labels = []

        self.image_size = IMAGE_SIZE
        self.transforms = transforms.Compose([
            transforms.Resize(self.image_size),
            transforms.CenterCrop(self.image_size),
            transforms.ToTensor(),
            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
        ])

        if class_to_label is None:
            self.class_to_label = {"face": 1, "not_face": 0}
        else:
            self.class_to_label = class_to_label

    def splitDataSet(self):
        indexes = list(range(len(self.images)))
        trainIndexes = []
        testIndexes = []
        for index in indexes:
            if random.random() < TRAIN_VALIDATION_SPLIT:
                trainIndexes.append(index)
            else:
                testIndexes.append(index)
        trainSet = ImageClassifierDataset()
        trainSet.images = [self.images[i] for i in trainIndexes]
        trainSet.labels = [torch.tensor(self.labels[i]) for i in trainIndexes]

        torch.stack(trainSet.images)
        torch.stack(trainSet.labels)

        testSet = ImageClassifierDataset()
        testSet.images = [self.images[i] for i in testIndexes]
        testSet.labels = [torch.tensor(self.labels[i]) for i in testIndexes]

        torch.stack(testSet.images)
        torch.stack(testSet.labels)


        print(sum(trainSet.labels))

        print(sum(testSet.labels))
        return trainSet, testSet

    def loadData(self):
        self.processDirectory("./data/images_faces", "face", 400)
        self.processDirectory("./data/256_ObjectCategories/257.clutter", "not_face", 200)

    def processImages(self, image_list, image_classes):
        for image, image_class in zip(image_list, image_classes):
            self.images.append(self.transforms(image))
            self.labels.append(self.class_to_label[image_class])

    def processDirectory(self, dir, label, size):
        image_list = []
        files = os.listdir(dir)
        np.random.shuffle(files)
        for imageFile in files[:size]:
            image_list.append(Image.open(f"{dir}/{imageFile}"))
        self.processImages(image_list, [label for _ in range(len(image_list))])

    def __getitem__(self, index):
        return self.images[index], self.labels[index]

    def __len__(self):
        return len(self.images)


if __name__ == '__main__':
    db = ImageClassifierDataset()
    print(len(db.images), len(db.labels))
