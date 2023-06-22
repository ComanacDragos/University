import os

import numpy as np
import tensorflow.keras as K
from matplotlib import pyplot as plt
from models import create_cnn
from data_generator import TextDataGenerator
from utils import to_json
from tensorflow.keras.utils import plot_model


def plot_history(history):
    rows = 1
    cols = 3
    plt.subplot(rows, cols, 1)
    plt.plot(history['accuracy'], label='accuracy')
    plt.plot(history['val_accuracy'], label='val_accuracy')
    # plt.plot(history.history['lr'], label='lr')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.ylim([0, 1])
    plt.legend(loc='upper right')

    plt.subplot(rows, cols, 2)
    plt.plot(history['loss'], label='loss')
    plt.plot(history['val_loss'], label='val_loss')
    # plt.plot(history.history['lr'], label='lr')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    # plt.ylim([0, 1])
    plt.legend(loc='upper right')

    plt.subplot(rows, cols, 3)
    plt.plot(history['lr'], label='lr')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    # plt.ylim([0, 1])
    plt.legend(loc='upper right')

    plt.tight_layout()
    plt.show()


def train(model, train_generator, val_generator, optimizer, callbacks, epochs):
    model.compile(optimizer=optimizer,
                  loss=K.losses.SparseCategoricalCrossentropy(from_logits=True),
                  metrics=['accuracy'])
    return model.fit(train_generator, validation_data=val_generator, epochs=epochs,
                     callbacks=callbacks,
                     workers=os.cpu_count())


class CosineAnnealingScheduler(K.callbacks.Callback):
    def __init__(self, n_min, n_max, T):
        super(CosineAnnealingScheduler, self).__init__()
        self.n_min = n_min
        self.n_max = n_max
        self.T = T
        self.learning_rates = {
            # 0: 1e-3
        }

    def on_epoch_begin(self, epoch, logs=None):
        if not hasattr(self.model.optimizer, "lr"):
            raise ValueError('Optimizer must have a "lr" attribute.')
        if epoch not in self.learning_rates:
            scheduled_lr = self.n_min + (1 / 2) * (self.n_max - self.n_min) * (1 + np.cos(epoch / self.T * np.pi))
        else:
            scheduled_lr = self.learning_rates[epoch]
        K.backend.set_value(self.model.optimizer.lr, scheduled_lr)
        print(f"\nEpoch {epoch + 1}: Learning rate is {scheduled_lr}.")


if __name__ == '__main__':
    batch_size = 8
    epochs = 20
    initial_lr = 5e-4
    model_type = "resnet"
    experiment = f"desire_{model_type}_batch_size_{batch_size}_epochs_{epochs}_lr_{initial_lr}"
    #csv = "csv/news_large.csv"
    #csv = 'data/news_large_val.csv'
    csv = 'data/rodesire_shuffled.csv'
    path = f"weights/{experiment}"
    if os.path.isdir(path):
        print(f"directory {path} exists")
    else:
        print(f"creating {path}")
        os.mkdir(path)

    _train_generator = TextDataGenerator(
        csv, 'train', batch_size, shuffle=True
    )
    _val_generator = TextDataGenerator(
        csv, 'val', 719,
    )

    _model = create_cnn(
        input_shape=(len(_train_generator.ALPHABET), _train_generator.MAX_LENGTH),
        no_classes=len(_train_generator.CLASSES),
        model_type=model_type
    )
    _model.summary()
    plot_model(_model, to_file=f'weights/{experiment}/model.png', show_shapes=True, show_layer_names=True)

    _optimizer = K.optimizers.Adam(learning_rate=initial_lr)
    _callbacks = [
        #K.callbacks.LearningRateScheduler(lambda epoch, lr: lr),
        K.callbacks.TerminateOnNaN(),
        K.callbacks.EarlyStopping(patience=5, min_delta=1e-4, verbose=2),
        K.callbacks.TensorBoard(log_dir=f'weights/{experiment}/tensorboard/'),
        K.callbacks.ModelCheckpoint(
            filepath=f'weights/{experiment}/model',
            save_best_only=True,
            verbose=2,
            monitor='val_accuracy'
        ),
        K.callbacks.ReduceLROnPlateau(patience=2, factor=0.5, verbose=1)
        #CosineAnnealingScheduler(5e-6, initial_lr, epochs)
    ]

    history = train(_model, _train_generator, _val_generator, _optimizer, _callbacks, epochs)
    history = history.history
    for k, v in history.items():
        history[k] = [float(x) for x in v]
    to_json(history, f'weights/{experiment}/history.json')
    plot_history(history)
