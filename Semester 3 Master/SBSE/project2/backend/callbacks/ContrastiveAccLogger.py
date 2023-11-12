import tensorflow as tf
from backend.callbacks.LoggableCallback import LoggableCallback
from backend.trainer.state import EvalState
import pandas as pd
import matplotlib.pyplot as plt
from backend.utils import logger


class ContrastiveAccLogger(LoggableCallback):
    def __init__(self, *args, threshold=0.5, **kwargs):
        super().__init__(*args, **kwargs)
        self.threshold = threshold
        self.best_acc = -1
        self._create_csv(self.csv_path, ['epoch', 'duplicate_acc', 'not_duplicate_acc', 'mean_acc'])

    def on_predict_end(self, logs: EvalState = None):
        csv = pd.read_csv(self.csv_path)

        predictions = tf.where(logs.predictions < self.threshold, 0, 1)
        no_samples = len(predictions)
        acc = tf.reduce_sum(predictions, axis=0)

        duplicate_acc = (acc[0] / no_samples).numpy()
        not_duplicate_acc = ((no_samples - acc[1]) / no_samples).numpy()

        mean_acc = (duplicate_acc + not_duplicate_acc) / 2

        if mean_acc > self.best_acc:
            self.best_acc = mean_acc
            logger.log(f"Found better model with acc {mean_acc} at epoch {logs.epoch}, saving...")
            logs.model.save(self.output_path / 'checkpoint')

        csv.loc[len(csv)] = [
            logs.epoch,
            duplicate_acc,
            not_duplicate_acc,
            mean_acc
        ]

        duplicate_acc = [round(x, 9) for x in csv.loc[:, 'duplicate_acc']]
        not_duplicate_acc = [round(x, 9) for x in csv.loc[:, 'not_duplicate_acc']]
        mean_acc = [round(x, 9) for x in csv.loc[:, 'mean_acc']]
        epochs = [int(x) for x in csv.loc[:, 'epoch']]
        self.plot_acc(duplicate_acc, not_duplicate_acc, mean_acc, epochs)

        csv.to_csv(
            self.csv_path, index=False,
            float_format=lambda x: round(x, 9)
        )

    def plot_acc(self, duplicate_acc, not_duplicate_acc, mean_acc, epochs):
        plt.plot(epochs, duplicate_acc, label='duplicate_acc')
        plt.plot(epochs, not_duplicate_acc, label='not_duplicate_acc')
        plt.plot(epochs, mean_acc, label='mean_acc')
        plt.xlabel('Epochs')
        plt.ylabel('Acc')
        plt.legend()
        plt.savefig(self.output_path / 'acc.png')
        plt.clf()
