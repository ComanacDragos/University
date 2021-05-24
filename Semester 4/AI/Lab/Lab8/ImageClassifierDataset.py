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
import sys


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
            self.class_to_label = {"face": 1.0, "not_face": 0.0}
        else:
            self.class_to_label = class_to_label

    def splitDataSet(self):
        imageToLabels = list(zip(self.images, self.labels))
        np.random.shuffle(imageToLabels)
        indexes = list(range(len(imageToLabels)))
        trainIndexes = []
        testIndexes = []
        for index in indexes:
            if random.random() < TRAIN_VALIDATION_SPLIT:
                trainIndexes.append(index)
            else:
                testIndexes.append(index)
        trainSet = ImageClassifierDataset()
        trainSet.images = [imageToLabels[i][0] for i in trainIndexes]
        trainSet.labels = [torch.tensor([imageToLabels[i][1]]) for i in trainIndexes]

        trainSet.images = torch.stack(trainSet.images)
        trainSet.labels = torch.stack(trainSet.labels)

        testSet = ImageClassifierDataset()
        testSet.images = [imageToLabels[i][0] for i in testIndexes]
        testSet.labels = [torch.tensor([imageToLabels[i][1]]) for i in testIndexes]

        testSet.images = torch.stack(testSet.images)
        testSet.labels = torch.stack(testSet.labels)

        print(f"Faces in train: {sum(trainSet.labels)}")
        print(f"Faces in test: {sum(testSet.labels)}")

        return trainSet, testSet

    def loadData(self):
        self.processDirectory("./data/images_faces_subset", "face", 1000)
        #self.processDirectory("./data/159.people", "face", 200)
        self.processDirectory("./data/253.faces-easy-101", "face", 400)

        self.processDirectory("./data/257.clutter", "not_face", 800)
        self.processNestedDirectory("./data/256_ObjectCategories", "not_face")

    def processImages(self, image_list, image_classes):
        for image, image_class in zip(image_list, image_classes):
            img = np.array(image)
            if len(img.shape) == 2:
                self.images.append(self.transforms(Image.fromarray(np.stack((img,) * 3, axis=-1))))
            else:
                self.images.append(self.transforms(image))
            self.labels.append(self.class_to_label[image_class])

    def processDirectory(self, dir, label, size):
        print(dir)
        image_list = []
        files = os.listdir(dir)
        np.random.shuffle(files)
        for imageFile in files[:size]:
            image_list.append(Image.open(f"{dir}/{imageFile}"))
        self.processImages(image_list, [label for _ in range(len(image_list))])

    def processNestedDirectory(self, dir, label):
        for subDir in os.listdir(dir):
            self.processDirectory(f"{dir}/{subDir}", label, NOT_FACE_IMAGES_PER_DIR)

    def __getitem__(self, index):
        return self.images[index], self.labels[index]

    def __len__(self):
        return len(self.images)


if __name__ == '__main__':
    db = ImageClassifierDataset()
    print(len(db.images), len(db.labels))
