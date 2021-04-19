import csv
import matplotlib.pyplot as plt
from random import uniform
import numpy as np


def loadData(fileName, firstVal, secondVal, outputLabel):
    data = []
    dataNames = []
    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count += 1
    selectedVariable = dataNames.index(firstVal)
    secondVariable = dataNames.index(secondVal)
    inputs = [(float(data[i][selectedVariable]), float(data[i][secondVariable])) for i in range(len(data))]
    selectedOutput = dataNames.index(outputLabel)
    outputs = [str(data[i][selectedOutput]) for i in range(len(data))]

    return inputs, outputs


def plotData(inputs, outputs, colors):
    for class_ in colors:
        classInputs = [x for index, x in enumerate(inputs) if outputs[index] == class_]
        plt.scatter([x[0] for x in classInputs], [x[1] for x in classInputs], label="stars", color=colors[class_],
                    marker="*", s=10)


def plotCentroids(centroids, color='purple'):
    plt.scatter([x[0] for x in centroids], [x[1] for x in centroids], label="stars", color=color,
                marker="*", s=50)


def plotComputedData(centroidToInputs, centroidToClass, colors):
    for centroid, inputs in centroidToInputs.items():
        plt.scatter([x[0] for x in inputs], [x[1] for x in inputs], label="stars", color=colors[centroidToClass[centroid]],
                    marker="*", s=10)

def getDomain(inputs):
    firstCol = [x[0] for x in inputs]
    secondCol = [x[1] for x in inputs]
    return (min(firstCol), min(secondCol)), (max(firstCol), max(secondCol))


def generateCentroids(domain, noClasses=4):
    centroids = set()
    (xBottom, yBottom), (xTop, yTop) = domain
    while len(centroids) != noClasses:
        centroids.add((uniform(xBottom, xTop), uniform(yBottom, yTop)))
    return centroids


def euclideanDistance(leftPos, rightPos):
    return np.linalg.norm(np.array(leftPos) - np.array(rightPos))


def solver(centroidsSet, inputs, outputs):
    centroids = list(centroidsSet)[:]
    noChange = True

    centroidToInputs = {centroid: [] for centroid in centroids}
    while noChange:
        noChange = False
        inputToCentroid = {}
        for input in inputs:
            inputToCentroid[input] = min(centroids, key=lambda centroid: euclideanDistance(input, centroid))

        centroidToInputs = {
            centroid: [input for input, inputCentroid in inputToCentroid.items() if inputCentroid == centroid]
            for centroid in centroids}

        newCentroids = [(np.mean([x[0] for x in sets]), np.mean([x[1] for x in sets]))
                        for sets in centroidToInputs.values()]

        for newCentroid in newCentroids:
            noChange = noChange or newCentroid not in centroids

        if noChange:
            centroids = newCentroids

    return centroidToInputs


inputs, outputs = loadData('dataset.csv', 'val1', 'val2', 'label')
centroids = generateCentroids(getDomain(inputs))

colors = {
    'A': 'green',
    'B': 'blue',
    'C': 'brown',
    'D': 'red'
}

print('starting...')
centroidToInputs = solver(centroids, inputs, outputs)
print('done...')

centroidToClass = {centroid: class_ for centroid, class_ in zip(centroidToInputs.keys(), colors.keys())}

print(centroidToClass)

plt.subplot(1, 2, 2)
plotData(inputs, outputs, colors)
plt.title('Ideal outputs')

plt.subplot(1, 2, 1)
plotComputedData(centroidToInputs, centroidToClass, colors)
plt.title('Computed outputs')
plt.show()
