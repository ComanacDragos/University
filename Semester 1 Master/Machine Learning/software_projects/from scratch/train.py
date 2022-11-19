from matplotlib import pyplot as plt

from model import SoftmaxClassifier
from data_generator import Cifar10DataGenerator
from utils import to_json


def plot_history(history):
    rows = 1
    cols = 3
    plt.subplot(rows, cols, 1)
    plt.plot(history['train_acc'], label='accuracy')
    plt.plot(history['val_acc'], label='val_accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.ylim([0, 1])
    plt.legend(loc='upper right')

    plt.subplot(rows, cols, 2)
    plt.plot(history['train_loss'], label='train_loss')
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


def train(model, train_generator, val_generator, epochs, reg_strength, lr, save_to):
    history = model.fit(train_generator, val_generator, epochs, reg_strength=reg_strength, lr=lr, save_to=save_to)
    plot_history(history)
    to_json(history, f'{save_to}.json')


if __name__ == '__main__':
    test_batch = 1
    epochs = 20
    lr = 1e-4
    bs = 256
    reg_strength = 1e-3
    experiment = f'test_batch_{test_batch}_bs_{bs}_lr_{lr}_reg_strength_{reg_strength}_epochs_{epochs}'

    train_batches = list(range(1, 7))
    train_batches.remove(test_batch)

    train_generator = Cifar10DataGenerator('cifar-10-batches-py', train_batches, batch_size=bs, flatten=True, shuffle=True, normalize=True, bias_trick=True)
    val_generator = Cifar10DataGenerator('cifar-10-batches-py', [test_batch], batch_size=bs, flatten=True, normalize=True, bias_trick=True)

    model = SoftmaxClassifier(32*32*3+1, 10)

    train(model, train_generator, val_generator, epochs, reg_strength, lr, save_to=f'weights/{experiment}')

