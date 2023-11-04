import sys

import pandas as pd
from utils import open_json
import numpy as np

mapping = open_json(sys.argv[1])
output_csv = sys.argv[2]

python_files = []
java_files = []
stage = []

for java_file, python_file in mapping.items():
    if python_file:
        python_files.append(python_file)
        java_files.append(java_file)
        if np.random.rand() < 0.8:
            stage.append('train')
        else:
            stage.append('val')

pd.DataFrame.from_dict({
    'original': java_files,
    'duplicate': python_files,
    'stage': stage
}).to_csv(output_csv, index=False)
