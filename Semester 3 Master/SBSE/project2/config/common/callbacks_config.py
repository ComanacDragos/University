from tensorflow.keras.callbacks import CallbackList
from backend.callbacks import LossLogger, ContrastiveAccLogger


class CallbacksConfig:
    @staticmethod
    def build(output_path):
        return CallbackList([
            LossLogger(output_path, 'train.csv'),
            ContrastiveAccLogger(output_path, 'eval.csv', threshold=0.5)
        ])
