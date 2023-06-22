import random
import sys

import pandas as pd
import collections

classes = ['Fulfilled', 'Unfulfilled', 'Unknown']
data = pd.read_csv('rodesire_shuffled.csv', sep=';')

out = 'rodesire_shuffled.csv'

print(len(data))

categories = data.loc[:, 'category']

freq = collections.Counter(categories)

print(freq)
# sys.exit(0)
final_data = None
for cls in classes:
    cls_data = data[data['category'] == cls]

    train = cls_data[cls_data['split'] == 'train']
    val = cls_data[cls_data['split'] == 'val']

    print(cls, len(cls_data))
    print("train", len(train))
    print('val', len(val))
    continue
    train_samples = int(len(cls_data) * 0.8)
    val_samples = len(cls_data) - train_samples

    split_list = [*['train'] * train_samples, *['val'] * val_samples]
    random.shuffle(split_list)
    cls_data['split'] = split_list
    if final_data is None:
        final_data = cls_data
    else:
        final_data = pd.concat([final_data, cls_data])

#final_data.to_csv(out, sep=';', index=False)