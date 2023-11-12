import tensorflow as tf
import numpy as np

data = tf.keras.datasets.mnist

(X_train, Y_train), (X_test, Y_test) = data.load_data()

print(np.max(X_test), np.mean(X_test))