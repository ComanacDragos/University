import pandas as pd
from collections import Counter

data = pd.read_csv('laptop_dataset_processed_v3.csv')

for col in data.columns:
    if col == 'id':
        continue

    print(col)
    samples = sorted(data.loc[:, col])
    freq = Counter(samples)

    print(", ".join([f"{k} ({v})" for k, v in freq.items()]))

    print()

