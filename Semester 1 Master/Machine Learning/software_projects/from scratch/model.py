import numpy as np
from time import perf_counter
from evaluation import compute_accuracy, compute_confusion_matrix
import os


def softmax(x):
    axis = 1 if len(x.shape) == 2 else None
    x_stabilized = x - np.max(x, axis=axis, keepdims=True)
    return np.exp(x_stabilized) / np.sum(np.exp(x_stabilized), axis=axis, keepdims=True)


class SoftmaxClassifier:
    def __init__(self, input_shape, num_classes):
        self.input_shape = input_shape
        self.num_classes = num_classes
        self.W = None
        self.initialize()

    def initialize(self):
        self.W = np.random.randn(self.input_shape - 1, self.num_classes) * 0.001
        self.W = np.concatenate([self.W, np.ones((1, self.num_classes))], axis=0)  # bias trick

    def predict_probability(self, X):
        return softmax(X.dot(self.W))

    def predict_label(self, X):
        return np.argmax(X.dot(self.W), axis=1)

    def run_epoch(self, data_generator, reg_strength, lr):
        losses = []
        pred = []
        gt = []
        for i in range(len(data_generator)):
            X_batch, y_batch = data_generator[i]
            current_bs = len(X_batch)

            output = X_batch.dot(self.W)

            pred += np.argmax(output, axis=1).tolist()
            gt += y_batch.tolist()

            stabilized_output = output - np.max(output, axis=1, keepdims=True)
            loss = -stabilized_output[range(current_bs), y_batch].reshape(current_bs, 1) \
                   + np.log(np.sum(np.exp(stabilized_output), axis=1, keepdims=True))

            loss = np.mean(loss) + reg_strength * np.sum(np.power(self.W, 2))

            if lr is not None:
                CT = softmax(output)
                CT[range(current_bs), y_batch] -= 1
                dW = X_batch.T.dot(CT) + reg_strength * self.W
                self.W -= lr * dW

            losses.append(loss)
        return np.mean(losses), compute_accuracy(compute_confusion_matrix(gt, pred))

    def fit(self, train_generator, val_generator, epochs=100, reg_strength=1e3, lr=1e-3, save_to=None):
        history = {
            'lr': [],
            'train_loss': [],
            'val_loss': [],
            'train_acc': [],
            'val_acc': [],
        }
        no_improvement = 0
        best = -1
        prev_path = None
        for epoch in range(epochs):
            start = perf_counter()
            train_loss, train_acc = self.run_epoch(train_generator, reg_strength, lr)
            val_loss, val_acc = self.run_epoch(val_generator, reg_strength, None)
            time = perf_counter()-start
            print(f'Epoch {epoch+1}/{epochs} '
                  f'Time {time} '
                  f'Train loss {train_loss} '
                  f'Val loss {val_loss} '
                  f'Train acc {train_acc} '
                  f'Val acc {val_acc} '
                  f'Learning rate {lr}'
                  )
            history['lr'].append(lr)
            history['train_loss'].append(train_loss)
            history['val_loss'].append(val_loss)
            history['train_acc'].append(train_acc)
            history['val_acc'].append(val_acc)
            if len(history['val_loss']) > 1:
                if history['val_loss'][-2] - history['val_loss'][-1] < 1e-2:
                    no_improvement += 1
                    if no_improvement >= 3:
                        lr /= 2
                        no_improvement = 0
                else:
                    no_improvement = 0
            if save_to and val_acc > best:
                best = val_acc
                new_path = f'{save_to}_best_epoch_{epoch+1}_acc_{val_acc}.npy'
                self.save(new_path)
                if prev_path:
                    os.remove(prev_path)
                prev_path = new_path

        return history

    def load(self, path):
        self.W = np.load(path)

    def save(self, path):
        np.save(path, self.W)
