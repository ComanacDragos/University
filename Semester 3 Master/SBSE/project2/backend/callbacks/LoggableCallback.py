import os

from tensorflow.keras.callbacks import Callback
from pathlib import Path
import pandas as pd


class LoggableCallback(Callback):
    def __init__(self, output_path, csv_name):
        super().__init__()
        self.output_path = Path(output_path)
        if not self.output_path.exists():
            os.makedirs(self.output_path)
        self.csv_path = self.output_path / csv_name

    @staticmethod
    def _create_csv(csv_path, header):
        pd.DataFrame({k: [] for k in header}).to_csv(csv_path, index=False)
