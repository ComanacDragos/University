import tensorflow.keras as K
import tensorflow as tf


def process_data(X):
    X = K.utils.normalize(X)
    X = tf.expand_dims(X, axis=-1)
    return X


def createModel(input_shape, num_classes, optimizer, loss, metrics):
    inputs = K.layers.Input(input_shape)
    x = K.layers.Conv2D(filters=64, kernel_size=(3, 3), activation='relu')(inputs)
    x = K.layers.Conv2D(filters=128, kernel_size=(3, 3), padding="same", activation='relu')(x)
    x = K.layers.MaxPool2D()(x)
    x = K.layers.Conv2D(filters=256, kernel_size=(3, 3), padding="same", activation='relu')(x)
    x = K.layers.MaxPool2D()(x)
    x = K.layers.Flatten()(x)
    x = K.layers.Dense(num_classes, activation='softmax')(x)

    model = K.models.Model(inputs=inputs, outputs=x)

    model.compile(optimizer=optimizer, loss=loss, metrics=[metrics])

    return model
