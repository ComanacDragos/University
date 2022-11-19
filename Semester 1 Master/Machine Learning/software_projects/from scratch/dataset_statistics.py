from data_generator import Cifar10DataGenerator
import numpy as np


def counts():
    ds = Cifar10DataGenerator("cifar-10-batches-py", list(range(1, 7)), 1, flatten=True)
    print('Count all')
    print(f'Dataset length: {len(ds.X)}')
    print(f'Counts: {np.unique(ds.y, return_counts=True)}')

    for i, ds in enumerate([Cifar10DataGenerator("cifar-10-batches-py", [x], 1, flatten=True) for x in range(1, 7)]):
        print(f'Batch {i + 1}')
        print(f'Dataset length: {len(ds.X)}')
        print(f'Counts: {np.unique(ds.y, return_counts=True)}')


def write_matrix(matrix, file):
    with open(file, 'w') as f:
        for i in range(len(matrix)):
            line = matrix[i, :].tolist()
            line = [str(round(x, 2)) for x in line]
            f.write(f'{",".join(line)}\n')


def normalize(x):
    return (x - np.mean(x)) / np.std(x)


def pearson():
    ds = Cifar10DataGenerator("cifar-10-batches-py", list(range(1, 7)), 1, flatten=False)
    print(ds.X.shape, np.reshape(ds.y, (-1, 1)).shape)
    X_simplified = np.reshape(np.mean(np.reshape(ds.X, (len(ds.X), 4, 4, -1)), axis=-1), (len(ds.X), -1))
    print(X_simplified.shape)

    features = np.concatenate([X_simplified, np.reshape(ds.y, (-1, 1))], axis=1)
    print(features.shape)
    no_features = features.shape[1]

    correlation_matrix = np.zeros((no_features, no_features))
    independence_matrix = np.zeros((no_features, no_features))

    for i in range(no_features):
        for j in range(i, no_features):
            print(i, j)
            X = features[:, i]
            Y = features[:, j]
            cov = np.mean((X - np.mean(X)) * (Y - np.mean(Y))) / (np.std(X) * np.std(Y))
            correlation_matrix[i, j] = cov
            correlation_matrix[j, i] = cov

            X = normalize(X)
            Y = normalize(Y)
            independence = np.sum(np.square(X - Y) / (Y + 1e-9))
            independence_matrix[i, j] = independence
            independence_matrix[j, i] = independence

    write_matrix(correlation_matrix, 'documentation/correlation.csv')
    write_matrix(normalize(independence_matrix), 'documentation/independence.csv')


if __name__ == '__main__':
    # counts()
    pearson()
    # with open('documentation/features.csv', 'w') as f:
    #    for i in range(4):
    #        line = [str(i*4+c+1) for c in range(4)]
    #        f.write(f'{",".join(line)}\n')
