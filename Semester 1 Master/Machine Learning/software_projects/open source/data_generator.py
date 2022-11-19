import os
import pickle

import numpy as np
import tensorflow as tf
from matplotlib import pyplot as plt


def _load_batch(path):
    with open(path, 'rb') as f:
        data = pickle.load(f, encoding='latin1')
    X = data['data']
    y = data['labels']
    X = X.reshape(X.shape[0], 3, 32, 32)
    X = np.transpose(X, axes=[0, 2, 3, 1])
    return X, np.asarray(y)


class Cifar10DataGenerator(tf.keras.utils.Sequence):
    CLASSES = ['airplane', 'automobile', 'bird', 'cat', 'deer',
               'dog', 'frog', 'horse', 'ship', 'truck']

    def __init__(self, data_root, batches_to_load, batch_size, flatten, shuffle=False, limit_batches=None):
        self.X = []
        self.y = []
        for batch in batches_to_load:
            X_batch, y_batch = _load_batch(f'{data_root}/data_batch_{batch}')
            self.X.extend(X_batch)
            self.y.extend(y_batch)

        self.X = np.asarray(self.X) / 255.0
        self.y = np.asarray(self.y)

        if flatten:
            self.X = np.reshape(self.X, (len(self.X), -1))

        self.batch_size = batch_size
        self.shuffle = shuffle
        self.flatten = flatten

        if limit_batches:
            self.X = self.X[:limit_batches * self.batch_size]
            self.y = self.y[:limit_batches * self.batch_size]

        self.indices = np.arange(len(self.X))
        self.on_epoch_end()

    def __len__(self):
        """
        Returns the number of batches per epoch: the total size of the dataset divided by the batch size
        """
        return int(np.ceil(len(self.X) / self.batch_size))

    def __getitem__(self, index):
        batch_indices = self.indices[index * self.batch_size: (index + 1) * self.batch_size]
        if self.flatten:
            batch_x = self.X[batch_indices, :]
        else:
            batch_x = self.X[batch_indices, :, :, :]
        batch_y = self.y[batch_indices]
        return batch_x, batch_y

    def on_epoch_end(self):
        """"
        Called at the end of each epoch
        """
        # if required, shuffle your data after each epoch
        self.indices = np.arange(len(self.X))
        if self.shuffle:
            np.random.shuffle(self.indices)


if __name__ == '__main__':
    test_flatten = Cifar10DataGenerator("cifar-10-batches-py", [1, 2], 25, flatten=True)
    batch_x, batch_y = test_flatten[0]
    print(batch_x.shape, batch_y.shape)

    db = Cifar10DataGenerator("cifar-10-batches-py",
                              [1, 2],
                              25, shuffle=True, flatten=False)
    print(len(db))
    print(db.X.shape, db.y.shape)
    batch_x, batch_y = db[0]
    print(batch_x.shape, batch_y.shape)

    plt.figure(figsize=(10,10))
    for i in range(25):
        plt.subplot(5,5,i+1)
        plt.xticks([])
        plt.yticks([])
        plt.grid(False)
        plt.imshow(batch_x[i])
        plt.xlabel(Cifar10DataGenerator.CLASSES[batch_y[i]])
    plt.show()