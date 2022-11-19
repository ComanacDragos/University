import json
import pickle

import numpy as np


def to_json(obj, file):
    json_obj = json.dumps(obj, indent=4)
    with open(file, "w") as f:
        f.write(json_obj)


def open_json(file):
    with open(file) as f:
        return json.load(f)


def to_pickle(obj, file):
    with open(file, 'wb') as f:
        pickle.dump(obj, f)


def open_pickle(file):
    with open(file, 'rb') as f:
        return pickle.load(f)


def softmax(x, t=1):
    axis = 1 if len(x.shape) == 2 else None
    x_stabilized = x - np.max(x, axis=axis, keepdims=True)
    return np.exp(x_stabilized / t) / np.sum(np.exp(x_stabilized / t), axis=axis, keepdims=True)