import numpy as np
import seaborn as sn
import pandas as pd
import matplotlib.pyplot as plt

from utils import open_json, to_json
from data_generator import TextDataGenerator


def plot_confusion_matrix(conf_mat):
    # print(conf_mat)
    df_cm = pd.DataFrame(conf_mat, range(len(conf_mat)), range(len(conf_mat)))
    plt.figure(figsize=(15, 15))
    sn.set(font_scale=1.4)
    sn.heatmap(df_cm, annot=True, annot_kws={"size": 12}, fmt='g',
               xticklabels=TextDataGenerator.CLASSES,
               yticklabels=TextDataGenerator.CLASSES)
    plt.xlabel("Target")
    plt.ylabel("Predicted")
    plt.show()


def plot_roc_curve(tpr, fpr, scatter=True, ax=None):
    '''
    https://github.com/vinyluis/Articles/blob/main/ROC%20Curve%20and%20ROC%20AUC/ROC%20Curve%20-%20Multiclass.ipynb
    Plots the ROC Curve by using the list of coordinates (tpr and fpr).

    Args:
        tpr: The list of TPRs representing each coordinate.
        fpr: The list of FPRs representing each coordinate.
        scatter: When True, the points used on the calculation will be plotted with the line (default = True).
    '''
    if ax == None:
        plt.figure(figsize=(5, 5))
        ax = plt.axes()

    if scatter:
        sn.scatterplot(x=fpr, y=tpr, ax=ax)
    sn.lineplot(x=fpr, y=tpr, ax=ax)
    # sn.lineplot(x=[0, 1], y=[0, 1], color='green', ax=ax)
    # plt.xlim(-0.05, 1.05)
    # plt.ylim(-0.05, 1.05)
    plt.xticks(np.arange(0, 1, 0.2))
    plt.yticks(np.arange(0, 1, 0.2))
    plt.xlabel("False Positive Rate")
    plt.ylabel("True Positive Rate")


def compute_confusion_matrix(gt, pred, num_classes=len(TextDataGenerator.CLASSES)):
    conf_mat = np.zeros((num_classes, num_classes))
    np.add.at(conf_mat, (pred, gt), 1)
    return conf_mat


def compute_accuracy(conf_mat):
    return np.sum(np.diagonal(conf_mat)) / np.sum(conf_mat)


def compute_precision(conf_mat):
    denom = np.sum(conf_mat, axis=1)
    denom[denom == 0] = 1
    return np.diagonal(conf_mat) / denom


def compute_recall(conf_mat):
    denom = np.sum(conf_mat, axis=0)
    denom[denom == 0] = 1
    return np.diagonal(conf_mat) / denom


def compute_fscore(conf_mat):
    prec = compute_precision(conf_mat)
    rec = compute_precision(conf_mat)
    denom = prec + rec
    denom[denom == 0] = 1
    return 2 * prec * rec / denom


def compute_AUC_binary(gt, prob, steps):
    true_positive_rates = [0]
    false_positive_rates = [0]
    for threshold in np.linspace(0, 1, steps):
        pred = np.asarray([1 if p >= threshold else 0 for p in prob])
        conf_mat = compute_confusion_matrix(gt, pred, 2)
        recall = compute_recall(conf_mat)
        sens, spec = recall[0], recall[1]
        true_positive_rate = sens
        false_positive_rate = 1 - spec
        true_positive_rates.append(true_positive_rate)
        false_positive_rates.append(false_positive_rate)
    return true_positive_rates, false_positive_rates


def repeated_trapezium(x, y):
    n = len(x) - 1
    return (x[-1] - x[0]) / (2 * n) * (y[0] + y[-1] + 2 * np.sum(y[:-1]))


def compute_AUC(gt, prob, plot=False, steps=11, classes=TextDataGenerator.CLASSES):
    if plot:
        no_subplots = len(classes)//2 + len(classes) % 2
        plt.subplots(no_subplots, 2, figsize=(5, 10))
    class_AUC = []
    for c in range(len(classes)):
        binary_prob = prob[:, c]
        binary_gt = np.asarray([1 if y == c else 0 for y in gt])
        true_positive_rates, false_positive_rates = compute_AUC_binary(binary_gt, binary_prob, steps)
        class_AUC.append(repeated_trapezium(false_positive_rates, true_positive_rates))
        if plot:
            ax = plt.subplot(no_subplots, 2, c + 1)
            ax.set_title(classes[c])
            plot_roc_curve(true_positive_rates, false_positive_rates, ax=ax)
            ax.set_title(classes[c])
    if plot:
        plt.tight_layout()
        plt.show()
    return class_AUC


def map_results(class_results, classes=TextDataGenerator.CLASSES):
    return {cls: cls_val for cls, cls_val in zip(classes, class_results)}


def process_results(results_dir, output_metrics, plot=False):
    results = open_json(f'{results_dir}/results.json')
    _gt, _pred, _prob = np.asarray(results['gt']), np.asarray(results['pred']), np.asarray(results['prob'])
    _conf_mat = compute_confusion_matrix(_gt, _pred)

    print('gt shape', _gt.shape)
    print('pred shape', _pred.shape)
    print('prob shape', _prob.shape)
    print(set(_gt), set(_pred))

    metrics = {
        'accuracy': compute_accuracy(_conf_mat),
        'precision': map_results(compute_precision(_conf_mat)),
        'recall': map_results(compute_recall(_conf_mat)),
        'fscore': map_results(compute_fscore(_conf_mat)),
        'AUC': map_results(compute_AUC(_gt, _prob, steps=100, plot=plot)),
    }

    for k, v in metrics.items():
        if type(v) is dict:
            print(k)
            if k not in output_metrics:
                output_metrics[k] = {}
            for sub_k, sub_v in [('mean', np.mean([x for x in v.values()])), *list(v.items())]:
                print("\t", sub_k, "->", sub_v)
                if sub_k not in output_metrics[k]:
                    output_metrics[k][sub_k] = [sub_v]
                else:
                    output_metrics[k][sub_k].append(sub_v)
        else:
            print(k, "->", v)
            if k not in output_metrics:
                output_metrics[k] = [v]
            else:
                output_metrics[k].append(v)
    if plot:
        plot_confusion_matrix(_conf_mat)


if __name__ == '__main__':
    _results_dir = "weights/batch_size_32_epochs_5_lr_0.0001"
    _output_metrics = {}
    process_results(_results_dir, _output_metrics, plot=True)
    to_json(_output_metrics, f'{_results_dir}/metrics.json')
