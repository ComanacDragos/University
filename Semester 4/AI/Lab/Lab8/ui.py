from Net import *
from torchvision import transforms
from PIL import Image
import torch
import sys
import os

ann = Net()
ann.load_state_dict(torch.load("./weights/myModel.model"))
ann.eval()

transforms = transforms.Compose([
    transforms.Resize(IMAGE_SIZE),
    transforms.CenterCrop(IMAGE_SIZE),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
])

labelToClass = {1: "face", 0: "not_face"}


def runAll():
    dir = "./data/ui_images"
    for filename in os.listdir(dir):
        image = transforms(Image.open(f"{dir}/{filename}"))
        image = image.unsqueeze(0)
        output = ann(image)
        _, prediction = torch.max(output.data, 1)
        print(f"{filename} -- {labelToClass[prediction.numpy()[0]]} \t\toutput: {output.data}\n")


def runOne():
    while True:
        try:
            file = "./data/ui_images/" + input("Filename: ")
            image = transforms(Image.open(file))
            image = image.unsqueeze(0)
            output = ann(image)
            _, prediction = torch.max(output.data, 1)
            print(prediction)
        except Exception as exc:
            print("Error:", exc)


runAll()
