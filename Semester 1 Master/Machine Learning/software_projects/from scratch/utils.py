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

