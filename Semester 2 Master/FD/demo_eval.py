from demo_utils import *

data = tf.keras.datasets.mnist

(_, _), (X_test, Y_test) = data.load_data()

X_test = process_data(X_test)

print("Test data shape: ", X_test.shape)

model = K.models.load_model('model')
model.compile(metrics='accuracy')

print("Evaluate on test data")
results = model.evaluate(X_test, Y_test, batch_size=256)
