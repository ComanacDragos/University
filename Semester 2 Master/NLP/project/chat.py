import numpy as np

from data_generator import TextDataGenerator
import numpy as np
import tensorflow.keras as K

from data_generator import TextDataGenerator
from utils import softmax

experiment = "resnet_batch_size_128_epochs_25_lr_0.0002_7197_acc"

model = K.models.load_model(f'weights/{experiment}/model')

prompt = None
while prompt != 'exit':
    prompt = input(">> ")
    one_hot_encodings = np.zeros((len(TextDataGenerator.ALPHABET), TextDataGenerator.MAX_LENGTH))
    for i, char in enumerate(prompt[:TextDataGenerator.MAX_LENGTH].lower()):
        if (encoding_index := TextDataGenerator.ALPHABET.find(char)) != -1:
            one_hot_encodings[encoding_index, i] = 1
    results = model(np.expand_dims(one_hot_encodings, axis=0))
    results = softmax(results.numpy())
    print("Results:")
    for r, cls in zip(results[0], TextDataGenerator.CLASSES):
        print(f"{cls}: {str(r*100)[:5]}%")