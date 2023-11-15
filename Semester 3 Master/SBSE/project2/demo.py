from backend.enums import Stage
from output.second_train.config.contrastive_learning_config.data_generator_config import MethodDataGeneratorConfig
import tensorflow as tf
import numpy as np

MethodDataGeneratorConfig.ROOT = ""
data_generator = MethodDataGeneratorConfig.build(Stage.VAL)
input_shape = (len(MethodDataGeneratorConfig.ALPHABET), MethodDataGeneratorConfig.MAX_LENGTH)

original_data = np.asarray([data_generator.load_data('original.txt')])
target_duplicate_data = np.asarray([data_generator.load_data('target_duplicate.txt')])
target_not_duplicate_data = np.asarray([data_generator.load_data('target_not_duplicate.txt')])

model = tf.keras.models.load_model('output/second_train/checkpoint')
model.summary()

prediction = model([original_data, target_duplicate_data])
print(f"Similarity for duplicate: {prediction[0][0]}")

prediction = model([original_data, target_not_duplicate_data])
print(f"Similarity for non duplicate: {prediction[0][0]}")
