import csv
import matplotlib.pyplot as plt
from random import uniform
import numpy as np


def loadData(fileName, firstVal, secondVal, outputLabel):
    data = []
    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        rows = list(csv_reader)
        dataNames = rows[0]
        for row in rows[1:]:
            data.append(row)

    return [(float(data[i][dataNames.index(firstVal)]), float(data[i][dataNames.index(secondVal)]))
            for i in range(len(data))], \
           [str(data[i][dataNames.index(outputLabel)]) for i in range(len(data))]


def plotData(inputs, outputs, colors):
    for class_ in colors:
        classInputs = [x for index, x in enumerate(inputs) if outputs[index] == class_]
        plt.scatter([x[0] for x in classInputs], [x[1] for x in classInputs], label="stars", color=colors[class_],
                    marker="*", s=10)


def plotCentroids(centroids, color='purple'):
    return plt.scatter([x[0] for x in centroids], [x[1] for x in centroids], label="stars", color=color,
                       marker="*", s=100)


def plotComputedData(centroidToInputs, centroidToClass, colors):
    for centroid, inputs in centroidToInputs.items():
        plt.scatter([x[0] for x in inputs], [x[1] for x in inputs], label="stars",
                    color=colors[centroidToClass[centroid]],
                    marker="*", s=10)
    return plotCentroids(centroidToInputs.keys())


def generateCentroidToClass(centroidToInputs):
    centroids = list(centroidToInputs.keys())
    leftMost = min(centroids, key=lambda x: x[0])
    centroids.remove(leftMost)

    rightMost = max(centroids, key=lambda x: x[0])
    centroids.remove(rightMost)

    bottomMost = min(centroids, key=lambda x: x[1])
    centroids.remove(bottomMost)

    topMost = centroids[0]

    return {leftMost: 'A', topMost: 'B', rightMost: 'C', bottomMost: 'D'}
    # return {centroid: class_ for centroid, class_ in zip(centroidToInputs.keys(), colors.keys())}


def plotAll(inputs, outputs, centroidToInputs, colors):
    centroidToClass = generateCentroidToClass(centroidToInputs)
    plt.subplot(1, 2, 2)
    plotData(inputs, outputs, colors)
    plt.title('Ideal outputs')

    plt.subplot(1, 2, 1)
    points = plotComputedData(centroidToInputs, centroidToClass, colors)
    plt.title('Computed outputs')
    return points


def getDomain(inputs):
    firstCol = [x[0] for x in inputs]
    secondCol = [x[1] for x in inputs]
    return (min(firstCol), min(secondCol)), (max(firstCol), max(secondCol))


def generateCentroids(domain, noCentroids=4, tabu=None):
    centroids = set()
    (xBottom, yBottom), (xTop, yTop) = domain
    while len(centroids) != noCentroids:
        centroid = uniform(xBottom, xTop), uniform(yBottom, yTop)
        if tabu is not None and centroid not in tabu:
            centroids.add(centroid)
        else:
            centroids.add(centroid)
    return centroids


def euclideanDistance(leftPos, rightPos):
    return np.linalg.norm(np.array(leftPos) - np.array(rightPos))


def evalClassification(real, computed, labelNames):
    acc = sum([1 if realLabel == computedLabel else 0
               for realLabel, computedLabel in zip(real, computed)]) / len(inputs)

    precision = {}
    rappel = {}

    for label in labelNames:
        correct = sum([1 if realLabel == computedLabel == label else 0
                       for realLabel, computedLabel in zip(real, computed)])

        total = sum(
            [1 if computedLabel == label else 0 for realLabel, computedLabel in zip(real, computed)])

        precision[label] = correct / total

        total = sum(
            [1 if realLabel == label else 0 for realLabel, computedLabel in zip(real, computed)])

        rappel[label] = correct / total

    score = {class_: 2*P*R/(P+R) for (class_, P), R in zip(precision.items(), rappel.values())}
    return {'acc': acc, 'precision': precision, 'rappel': rappel, 'score': score}


def solver(centroidsSet, inputs, outputs):
    centroids = list(centroidsSet)[:]
    change = True

    centroidToInputs = {centroid: [] for centroid in centroids}
    while change:
        change = False
        inputToCentroid = {}
        for input in inputs:
            inputToCentroid[input] = min(centroids, key=lambda centroid: euclideanDistance(input, centroid))

        centroidToInputs = {
            centroid: [input for input, inputCentroid in inputToCentroid.items() if inputCentroid == centroid]
            for centroid in centroids}

        newCentroids = [(sum([x[0] for x in sets]) / len(sets), sum([x[1] for x in sets]) / len(sets)) if len(sets) != 0
                        else None
                        for centroid, sets in centroidToInputs.items()]

        validCentroids = [centroid for centroid in newCentroids if centroid is not None]
        if len(centroidsSet) - len(validCentroids) != 0:
            print('Empty centroid!')
            newCentroids = validCentroids + list(generateCentroids(getDomain(inputs),
                                                                   len(centroidsSet) - len(validCentroids),
                                                                   validCentroids))

        for newCentroid in newCentroids:
            change = change or newCentroid not in centroids

        if change:
            centroids = newCentroids
        else:
            centroidToClass = generateCentroidToClass(centroidToInputs)
            print(centroidToClass)
            print(colors)
            print('compute statistics...')

            inputToComputed = {}
            for centroid, set_ in centroidToInputs.items():
                for input in set_:
                    inputToComputed[input] = centroidToClass[centroid]
            computedLabels = [inputToComputed[input] for input in inputs]

            for val, result in evalClassification(outputs, computedLabels, colors.keys()).items():
                print(f"{val}: {result}")

        points = plotAll(inputs, outputs, centroidToInputs, colors)
        plt.pause(0.5)
        if change:
            points.remove()

    return centroidToInputs


inputs, outputs = loadData('dataset.csv', 'val1', 'val2', 'label')

colors = {
    'A': 'green',
    'B': 'blue',
    'C': 'brown',
    'D': 'red'
}

print('starting...')
solver(generateCentroids(getDomain(inputs)), inputs, outputs)
print('done...')
plt.show()

# plotAll(inputs, outputs, centroidToInputs, colors)
