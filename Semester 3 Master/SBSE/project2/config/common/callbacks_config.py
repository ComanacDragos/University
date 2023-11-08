from backend.enums import Stage
from keras.callbacks import CallbackList, ModelCheckpoint


class CallbacksConfig:
    @staticmethod
    def build():
        return {
            Stage.TRAIN: CallbackList([

            ]),
            Stage.VAL: [CallbackList([])]
        }
