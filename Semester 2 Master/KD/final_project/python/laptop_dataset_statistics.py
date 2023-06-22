import pandas as pd
from collections import Counter
import numpy as np


def handle_string_data(strings, name):
    print(f"{name} statistics")
    freq = Counter(strings)
    print(" - ".join([f"{k} ({v})" for k, v in freq.items()]))
    print("Different types: ", len(freq))


def company(data):
    handle_string_data(data.loc[:, 'Company'], 'Company')


def type_name(data):
    handle_string_data(data.loc[:, 'TypeName'], 'TypeName')


def inches(data):
    inches = data.loc[:, 'Inches']
    handle_string_data([str(x) for x in sorted(inches)], 'Inches')
    print('histogram', np.histogram(inches, bins=3))


def cpu(data):
    cpu_data = data.loc[:, 'Cpu']
    processed_cpu_data = []
    for sample in cpu_data:
        sample = sample.lower()
        if 'intel' in sample:
            processed_cpu_data.append('intel')
        elif 'amd' in sample:
            processed_cpu_data.append('amd')
        else:
            continue
    handle_string_data(processed_cpu_data, 'CPU')


def ram(data):
    handle_string_data(sorted(data.loc[:, 'Ram'], key=lambda x: int(x[:-2])), "RAM")


def memory(data):
    memory_data = data.loc[:, 'Memory']
    processed_memory_data = []
    for sample in memory_data:
        sample = sample.lower()
        if 'ssd' in sample and 'hdd' in sample:
            processed_memory_data.append("SSD + HDD")
        elif 'ssd' in sample:
            processed_memory_data.append('SSD')
        elif 'hdd' in sample:
            processed_memory_data.append('HDD')
        elif 'flash' in sample:
            processed_memory_data.append('flash')
        else:
            continue
    handle_string_data(sorted(processed_memory_data), 'Memory')


def gpu(data):
    memory_data = data.loc[:, 'Gpu']
    processed_memory_data = []
    for sample in memory_data:
        sample = sample.lower()
        if 'intel' in sample:
            processed_memory_data.append("Intel")
        elif 'amd' in sample:
            processed_memory_data.append('AMD')
        elif 'nvidia' in sample:
            processed_memory_data.append('Nvidia')
        else:
            continue
    handle_string_data(sorted(processed_memory_data), 'GPU')


if __name__ == '__main__':
    _data = pd.read_csv('laptop_price.csv')
    stats_to_compute = [
        company,
        type_name,
        inches,
        cpu,
        ram,
        memory,
        gpu
    ]
    for stat in stats_to_compute:
        stat(_data)
        print('\n')
