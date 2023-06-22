import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv("subset.csv")

print(data.columns)

exp = set(data.loc[:, 'experience_level'])
print(exp)

salaries = list(data.loc[:, 'salary_in_usd'])
#data.to_csv("processed.csv", index=False)

print(np.min(salaries), np.max(salaries))
h = np.histogram(salaries, bins=3)

ranges = h[1]
print(ranges)

salary_type = []

int_2_type = {
    0: 'low',
    1: 'medium',
    2: 'high'
}
for s in salaries:
    for i in range(1, len(ranges)):
        if ranges[i-1] <= s <= ranges[i]:
            salary_type.append(int_2_type[i-1])

data['salary_type'] = salary_type

data = data.drop_duplicates(subset=['experience_level', 'job_title', 'company_size', 'salary_type', 'remote_ratio'])
data.to_csv("processed.csv", index=False)