import sys

import pandas as pd
from backend.utils import open_json
import numpy as np

mapping = open_json(sys.argv[1])
output_csv = sys.argv[2]

python_files = []
java_files = []

for java_file, python_file in mapping.items():
    if python_file:
        python_files.append(python_file)
        java_files.append(java_file)

num_val = int(len(java_files) * 0.2)

stage = [1] * (len(java_files) - num_val) + [0] * num_val
np.random.shuffle(stage)
stage = ['train' if x == 1 else 'val' for x in
         stage
         ]


pd.DataFrame.from_dict({
    'original': java_files,
    'duplicate': python_files,
    'stage': stage
}).to_csv(output_csv, index=False)
