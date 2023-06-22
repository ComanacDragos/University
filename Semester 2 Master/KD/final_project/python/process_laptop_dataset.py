import pandas as pd
from collections import Counter
import numpy as np

data = pd.read_csv('laptop_price.csv')

ids = {}
samples = set()
output = pd.DataFrame(columns=[
    'id',
    'company',
    # 'inches',
    'cpu',
    'ram',
    'memory',
    'gpu'
])

i = 0
for _, row in data.iterrows():
    company, inches, cpu, ram, memory, gpu = row['Company'], row['Inches'], row['Cpu'], row['Ram'], row['Memory'], row[
        'Gpu']

    if inches < 12.8:
        screen_size = 'small'
    elif inches < 16:
        screen_size = 'medium'
    else:
        screen_size = 'large'

    cpu = cpu.lower()
    if 'intel' in cpu:
        cpu = 'intel'
    elif 'amd' in cpu:
        cpu = 'amd'
    else:
        continue

    ram = int(ram[:-2])
    # if ram < 8:
    #     ram = 'small'
    # elif ram < 16:
    #     ram = 'medium'
    # else:
    #     ram = 'large'

    memory = memory.lower()
    if 'ssd' in memory and 'hdd' in memory:
        memory = "SSD + HDD"
    elif 'ssd' in memory:
        memory = 'SSD'
    elif 'hdd' in memory:
        memory = 'HDD'
    elif 'flash' in memory:
        memory = 'flash'
    else:
        continue

    gpu = gpu.lower()
    if 'intel' in gpu:
        gpu = "Intel"
    elif 'amd' in gpu:
        gpu = 'AMD'
    elif 'nvidia' in gpu:
        gpu = 'Nvidia'
    else:
        continue

    sample = (company, cpu, ram, memory, gpu)
    if sample not in samples:
        if company in ids:
            ids[company] += 1
            laptop_id = f'{company}_{ids[company]}'
        else:
            laptop_id = f'{company}_1'
            ids[company] = 1

        output.loc[i] = (laptop_id, company, cpu, ram, memory, gpu)#(laptop_id, *sample[1:])
        i += 1
        samples.add(sample)

output.to_csv('laptop_dataset_processed_v4.csv', index=False)
