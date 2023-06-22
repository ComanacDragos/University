import random
import sys

import pandas as pd
import collections

classes = ['World', 'Sports', 'Business', 'Sci/Tech']
data = pd.read_csv('news.csv', sep=';')

train_samples = 30000
val_samples = 7500
out = 'news_large_val.csv'

print(len(data))

categories = data.loc[:, 'category']

freq = collections.Counter(categories)

print(freq)
#sys.exit(0)
final_data = None
for cls in classes:
    cls_data = data[data['category'] == cls][:train_samples+val_samples]
    print(cls, len(cls_data))

    split_list = [*['train']*train_samples, *['val']*val_samples]
    random.shuffle(split_list)
    cls_data['split'] = split_list
    if final_data is None:
        final_data = cls_data
    else:
        final_data = pd.concat([final_data, cls_data])

final_data.to_csv(out, sep=';', index=False)