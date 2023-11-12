from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
from utils import *


image = Image.open("original_v2.png").convert("L").resize((28, 28))
image = np.array(image)

image = np.max(image) - image
image[image > 0] = 255

showable_image = image

image = np.expand_dims(image, axis=0)

print(np.mean(image))
print(np.max(image))

image = process_data(image)
print(image.shape)

model = K.models.load_model('model_v0')

predicted_probabilities = model(image)
print("Raw probabilities output shape: ", predicted_probabilities.shape, predicted_probabilities)

predicted_digits = tf.argmax(predicted_probabilities, axis=-1)

print("Predicted: ", predicted_digits)


plt.imshow(showable_image, cmap='gray')
plt.show()

