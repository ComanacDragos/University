import os

from data_generator import TextDataGenerator
import tensorflow.keras as K
import tensorflow as tf
from utils import to_json, softmax

if __name__ == '__main__':
    experiment = 'desire_resnet_batch_size_8_epochs_20_lr_0.001_5424_acc'
    csv = 'data/rodesire_shuffled.csv'

    generator = TextDataGenerator(
        csv, 'val', 128,
    )

    model = K.models.load_model(f'weights/{experiment}/model')
    model.summary()

    pred_all = []
    gt_all = []
    pred_prob_all = []
    for i in range(len(generator)):
        print(f'{i+1}/{len(generator)}')
        X, y = generator[i]
        results = model(X)
        pred_classes = tf.argmax(results, axis=-1).numpy()
        a = softmax(results.numpy())
        pred_prob = softmax(results.numpy())  # [(list(range(len(results))), pred_classes)]

        pred_all += pred_classes.tolist()
        pred_prob_all += pred_prob.tolist()
        gt_all += y.tolist()
    print(f"no preds {len(pred_all)}  no gt {len(gt_all)}")

    path = f'weights/{experiment}/results.json'
    to_json({
        'pred': pred_all,
        'gt': gt_all,
        'prob': pred_prob_all
    }, path)


