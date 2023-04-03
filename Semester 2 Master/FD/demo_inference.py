from demo_utils import *
import matplotlib.pyplot as plt
import numpy as np

data = tf.keras.datasets.mnist

(_, _), (X_test, Y_test) = data.load_data()

X_test = process_data(X_test)

model = K.models.load_model('model')
model.summary()

idxs = np.random.randint(0, len(X_test), size=(9,))

X_test = tf.gather(X_test, idxs)
Y_test = tf.gather(Y_test, idxs)
print("Test data shape: ", X_test.shape)

predicted_probabilities = model(X_test)
print("Raw probabilities output shape: ", predicted_probabilities.shape)

predicted_digits = tf.argmax(predicted_probabilities, axis=-1)

print("Predicted: ", predicted_digits)
print("Real:      ", Y_test)

for i, (img, pred, real) in enumerate(zip(X_test, predicted_digits, Y_test), start=1):
    plt.subplot(3, 3, i)
    plt.imshow(img.numpy(), cmap='gray')
    plt.title(f"Pred: {pred.numpy()} Real: {real.numpy()}")
    plt.axis('off')

plt.tight_layout()
plt.show()

