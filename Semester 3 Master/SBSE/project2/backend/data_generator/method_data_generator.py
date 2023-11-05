import numpy as np
import tensorflow as tf
import pandas as pd
from backend.enums import Stage
from pathlib import Path


class MethodDataGenerator(tf.keras.utils.Sequence):
    def __init__(self, root, csv_path, batch_size, stage: Stage, alphabet, max_length):
        self.root = Path(root)
        self.data = pd.read_csv(csv_path)
        self.data = self.data[self.data['stage'] == stage.value]
        print(f"Loaded {csv_path} for {stage.value} - {len(self.data)} samples")
        self.batch_size = batch_size
        self.stage = stage
        self.alphabet = alphabet
        self.max_length = max_length

        self.indices = np.arange(len(self.data))
        self.on_epoch_end()

        self.cache = {}

    def __len__(self):
        """
        Returns the number of batches per epoch: the total size of the dataset divided by the batch size
        """
        length = int(np.ceil(len(self.data) / self.batch_size))
        # avoid batches of size 1
        if len(self.data) % self.batch_size == 1:
            length -= 1
        return length

    def process_data(self, data):
        one_hot_encodings = np.zeros((len(self.alphabet), self.max_length))
        for i, char in enumerate(data[:self.max_length].lower()):
            if (encoding_index := self.alphabet.find(char)) != -1:
                one_hot_encodings[encoding_index, i] = 1
        return one_hot_encodings

    def load_data(self, path):
        if path in self.cache:
            return self.cache[path]
        else:
            with open(self.root / path) as f:
                data = self.process_data("".join(f.readlines()))
                self.cache[path] = data
                return data

    def __getitem__(self, index):
        if index >= self.__len__():
            raise IndexError("Too large index")
        batch_indices = self.indices[index * self.batch_size: (index + 1) * self.batch_size]
        batch_data = self.data.loc[self.data.index[batch_indices]]
        batch_data = list(row for _, row in batch_data.iterrows())
        original_methods = []
        duplicate_methods = []
        not_duplicate_methods = []
        for i, row in enumerate(batch_data):
            original_methods.append(self.load_data(row['original']))
            duplicate_methods.append(self.load_data(row['duplicate']))
            not_duplicate_methods.append(self.load_data(batch_data[(i + 1) % len(batch_data)]['duplicate']))

        return np.stack(original_methods), np.stack(duplicate_methods), np.stack(not_duplicate_methods)

    def on_epoch_end(self):
        """"
        Called at the end of each epoch
        """
        # if required, shuffle your data after each epoch
        if self.stage == Stage.TRAIN:
            self.indices = np.arange(len(self.data))
            np.random.shuffle(self.indices)

    def decode_gt(self, text_encoding):
        indexes = np.argmax(text_encoding, axis=0)
        text = ""
        for i, index in enumerate(indexes):
            if np.sum(text_encoding[:, i]) > 0:
                text += self.alphabet[index]
            else:
                text += " "
        return text.strip()
