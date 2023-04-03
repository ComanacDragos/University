from demo_utils import *

data = tf.keras.datasets.mnist

(X_train, Y_train), (X_test, Y_test) = data.load_data()

X_train = process_data(X_train)
X_test = process_data(X_test)

print("Training data shape: ", X_train.shape)
print("Test data shape: ", X_test.shape)

model = createModel(input_shape=(28, 28, 1), num_classes=10, optimizer='adam',
                    loss='sparse_categorical_crossentropy',
                    metrics='accuracy')

model.summary()

model.fit(X_train, Y_train, epochs=3, batch_size=256, validation_split=0.2)

model.save("model")

