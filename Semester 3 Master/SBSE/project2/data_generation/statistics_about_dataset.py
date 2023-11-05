import sys

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv(sys.argv[1])

paths = list(data.loc[:, 'original']) + list(data.loc[:, 'duplicate'])

print(len(paths))

char_freq = {}
lengths = []

for i, path in enumerate(paths):
    if (i+1) % 100 == 0:
        print(f"{i+1}/{len(paths)}")
    with open(path) as f:
        file_length = 0
        for line in f.readlines():
            file_length += len(line)
            for char in line.lower():
                if char in char_freq:
                    char_freq[char] += 1
                else:
                    char_freq[char] = 1
        lengths.append(file_length)

print("="*100)
print("Len freq")
print("Mean", np.mean(lengths), "Std", np.std(lengths))
print("Min", np.min(lengths), "Max", np.max(lengths))

plt.hist(lengths, bins=10)
plt.show()

count = 1024
print("Less than", count, "->", len([x for x in lengths if x <= count]))


print("="*100)
print("Char freq")
for k, v in sorted(list(char_freq.items()), key=lambda x: -x[1]):
    print(k, "->", v)

print("".join(sorted(char_freq.keys())))
