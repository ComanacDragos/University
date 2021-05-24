from Net import *
from torchvision import transforms
from PIL import Image
import torch
import sys
import os

ann = Net()
ann.load_state_dict(torch.load("./weights/myModelV4.model"))
ann.eval()

transforms = transforms.Compose([
    transforms.Resize(IMAGE_SIZE),
    transforms.CenterCrop(IMAGE_SIZE),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
])

labelToClass = {1.0: "face", 0.0: "not_face"}


def runAll():
    dir = "./data/ui_images"
    #dir = "./data/images_faces"
    files = os.listdir(dir)
    images = [transforms(Image.open(f"{dir}/{filename}")) for filename in files]
    images = torch.stack(images)
    output = ann(images)
    predictions = ["face" if data[0] >= 0.5 else "not_face" for data in output.data.numpy()]

    for file, prediction, output in zip(files, predictions, output.data.numpy()):
        print(f"{file} -- {prediction} \t\toutput: {output}\n")


def runOne():
    while True:
        try:
            file = "./data/ui_images/" + input("Filename: ")
            image = transforms(Image.open(file))
            image = image.unsqueeze(0)
            output = ann(image)
            other, prediction = torch.max(output.data, 1)
            print(f"{labelToClass[prediction.numpy()[0]]} \t\toutput: {output.data}\n")
        except Exception as exc:
            print("Error:", exc)


runAll()
