import os

from data_generator import Cifar10DataGenerator
import tensorflow.keras as K
import tensorflow as tf
from utils import to_json, softmax

if __name__ == '__main__':
    experiment = 'batch_size_32_epochs_20_lr_0.0001'
    architecture = 'cnn'

    for test_batch in range(1, 7):
        generator = Cifar10DataGenerator(
            "cifar-10-batches-py",
            [test_batch],
            batch_size=32, flatten=architecture == 'ann'
        )

        model = K.models.load_model(f'weights/{architecture}/{experiment}/test_batch_{test_batch}')
        model.summary()

        pred_all = []
        gt_all = []
        pred_prob_all = []
        for i in range(len(generator)):
            print(f'{i+1}/{len(generator)} test_batch {test_batch}')
            X, y = generator[i]
            results = model(X)
            pred_classes = tf.argmax(results, axis=-1).numpy()
            a = softmax(results.numpy())
            pred_prob = softmax(results.numpy())  # [(list(range(len(results))), pred_classes)]

            pred_all += pred_classes.tolist()
            pred_prob_all += pred_prob.tolist()
            gt_all += y.tolist()
        print(f"no preds {len(pred_all)}  no gt {len(gt_all)}")

        path = f'results/{architecture}/{experiment}'
        if os.path.isdir(path):
            print(f"directory {path} exists")
        else:
            print(f"creating {path}")
            os.mkdir(path)
        to_json({
            'pred': pred_all,
            'gt': gt_all,
            'prob': pred_prob_all
        }, f'{path}/test_batch_{test_batch}.json')


