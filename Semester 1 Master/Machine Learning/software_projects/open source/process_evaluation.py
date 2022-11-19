import numpy as np
from utils import to_json, open_json


if __name__ == '__main__':
    metrics_path = 'results/ann/batch_size_32_epochs_20_lr_0.0001/metrics.json'
    metrics = open_json(metrics_path)

    analysis = {}

    for k, v in metrics.items():
        if type(v) is dict:
            if k not in analysis:
                analysis[k] = {}
            for sub_k, sub_v in v.items():
                analysis[k][sub_k] = {
                    'mean': np.mean(sub_v),
                    'std': np.std(sub_v),
                    'alpha': 1.96*np.std(sub_v)/np.sqrt(6)
                }
        else:
            analysis[k] = {
                'mean': np.mean(v),
                'std': np.std(v),
                'alpha': 1.96*np.std(v)/np.sqrt(6)
            }
    to_json(analysis, f'{metrics_path[:-5]}_analysis.json')