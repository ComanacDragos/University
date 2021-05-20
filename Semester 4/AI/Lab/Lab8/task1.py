from PIL import Image
from matplotlib import image
from matplotlib import pyplot


def taskA():
    image = Image.open("f1.jpg")
    print(image.format)
    print(image.mode)
    print(image.size)
    image.show()


def taskB():
    data = image.imread('f1.jpg')
    print(data.dtype)
    print(data.shape)
    print(data)
    pyplot.imshow(data)
    pyplot.show()


def taskC():
    image = Image.open('f1.jpg')
    print(image.size)
    image.thumbnail((100, 100))
    print(image.size)
    image.show()


#taskA()
#taskB()
taskC()
