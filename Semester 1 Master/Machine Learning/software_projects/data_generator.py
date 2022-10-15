import os
import pickle

import numpy as np
import tensorflow as tf


def _load_batch(path):
    with open(path, 'rb') as f:
        data = pickle.load(f, encoding='latin1')
    X = data['data']
    y = data['labels']
    X = X.reshape(X.shape[0], 3, 32, 32)
    X = np.transpose(X, axes=[0, 2, 3, 1])
    return X, np.asarray(y)


class Cifar10DataGenerator(tf.keras.utils.Sequence):
    def __init__(self, data_root, paths_to_load, batch_size, ):
        self.X = []
        self.y = []
        for batch in paths_to_load:
            X_batch, y_batch = _load_batch(batch)
            self.X.extend(X_batch)
            self.y.extend(y_batch)

        self.X = np.asarray(self.X)
        self.y = np.asarray(self.y)

    def __len__(self):
        pass

    def __getitem__(self, idx):
        pass

    def on_epoch_end(self):
        pass
