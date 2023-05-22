import numpy as np
import tensorflow as tf
import pandas as pd


class TextDataGenerator(tf.keras.utils.Sequence):
    CLASSES = ['World', 'Sports', 'Business', 'Sci/Tech']
    ALPHABET = "abcdefghijklmnopqrstuvwxyz0123456789-,;.!?:’’’/\\|_@#$%ˆ&*˜‘+-=<>()[]{}"
    MAX_LENGTH = 1014

    def __init__(self, csv_path, split, batch_size, shuffle=False):
        self.data = pd.read_csv(csv_path, sep=';')
        self.data = self.data[self.data['split'] == split]

        self.batch_size = batch_size
        self.shuffle = shuffle

        self.indices = np.arange(len(self.data))
        self.on_epoch_end()

    def __len__(self):
        """
        Returns the number of batches per epoch: the total size of the dataset divided by the batch size
        """
        return int(np.ceil(len(self.data) / self.batch_size))

    def __getitem__(self, index):
        batch_indices = self.indices[index * self.batch_size: (index + 1) * self.batch_size]
        batch_data = self.data.loc[self.data.index[batch_indices]]
        classes = []
        samples = []
        for _, row in batch_data.iterrows():
            category = row['category']
            title = row['title']
            description = row['description']
            print(category, " : ", title + ' ' + description)
            classes.append(self.CLASSES.index(category))
            one_hot_encodings = np.zeros((len(self.ALPHABET), self.MAX_LENGTH))
            for i, char in enumerate((title + ' ' + description)[:self.MAX_LENGTH].lower()):
                if (encoding_index := self.ALPHABET.find(char)) != -1:
                    one_hot_encodings[encoding_index, i] = 1
            samples.append(one_hot_encodings)
        return np.stack(samples), np.asarray(classes)

    def on_epoch_end(self):
        """"
        Called at the end of each epoch
        """
        # if required, shuffle your data after each epoch
        if self.shuffle:
            self.indices = np.arange(len(self.data))
            np.random.shuffle(self.indices)

    def decode_gt(self, text_encoding, class_index):
        indexes = np.argmax(text_encoding, axis=0)
        text = ""
        for i, index in enumerate(indexes):
            if np.sum(text_encoding[:, i]) > 0:
                text += self.ALPHABET[index]
            else:
                text += " "
        return text.strip(), self.CLASSES[class_index]


if __name__ == '__main__':
    db = TextDataGenerator("data/news.csv", 'val', 2)
    print(len(db))
    encodings, classes = db[0]
    text, cls = db.decode_gt(encodings[0], classes[0])

    print('\n\n')
    print(cls, ": ", text)

    text, cls = db.decode_gt(encodings[1], classes[1])
    print(cls, ": ", text)
