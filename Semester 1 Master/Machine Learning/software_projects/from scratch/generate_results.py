import os

import numpy as np

from model import SoftmaxClassifier
from data_generator import Cifar10DataGenerator
from utils import to_json


def generate_results(model_path):
    test_batch = model_path.split('/')[-1][11]
    print(test_batch)

    data_generator = Cifar10DataGenerator('cifar-10-batches-py', [test_batch], batch_size=32, flatten=True, normalize=True, bias_trick=True)
    model = SoftmaxClassifier(32*32*3+1, 10)
    model.load(model_path)
    pred = []
    gt = []
    prob = []
    for i in range(len(data_generator)):
        print(f'{i+1}/{len(data_generator)}')
        X_batch, y_batch = data_generator[i]
        prob_batch = model.predict_probability(X_batch)

        pred += np.argmax(prob_batch, axis=1).tolist()
        gt += y_batch.tolist()
        prob += prob_batch.tolist()
    to_json({
        'pred': pred,
        'gt': gt,
        'prob': prob
    }, f'results/test_batch_{test_batch}.json')


if __name__ == '__main__':
    for path in os.listdir('weights'):
        if 'npy' in path:
            generate_results(f'weights/{path}')
