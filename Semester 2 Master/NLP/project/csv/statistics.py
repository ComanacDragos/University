import numpy as np
import pandas as pd

data = pd.read_csv('rodesire_shuffled.csv', sep=';')
data = data[data['split'] == 'val']

stats = {}

alphabet = {}

for _, row in data.iterrows():
    category = row['category']

    description = row['description']
    if 'title' in data.columns:
        title = row['title']
        description = f'{title} {description}'
    for c in description:
        if c not in alphabet:
            alphabet[c] = 1
        else:
            alphabet[c] += 1
    if category not in stats:
        stats[category] = [len(description)]
    else:
        stats[category].append(len(description))

all = []

count = 0
count_all = 0
for k, v in stats.items():
    print(k)
    print("mean", np.mean(v))
    print("std", np.std(v))
    print("min", np.min(v))
    print("max", np.max(v))
    print("\n\n")
    all += v

    for x in v:
        if x < 2048:
            count+=1
    count_all += len(v)


print("ALL")
print("mean", np.mean(all))
print("std", np.std(all))
print("min", np.min(all))
print("max", np.max(all))

print()
print(count, count_all)

print()

for k, v in alphabet.items():
    print(k, " -> ", v)
print("".join(sorted(list(alphabet.keys()))))