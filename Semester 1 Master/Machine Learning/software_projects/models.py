import tensorflow.keras as K
from tensorflow.keras.layers import Input, Dense, Conv2D, BatchNormalization, GlobalAvgPool2D


def create_dense_layer(output_units):
    return Dense(output_units, activation='relu')


def create_conv_layer(filters, strides=1, kernel_size=3):
    return Conv2D(filters,
                  kernel_size=kernel_size,
                  padding='same',
                  strides=strides,
                  activation='relu',
                  kernel_initializer=K.initializers.HeNormal(),
                  kernel_regularizer=K.regularizers.l2()
            )


def create_ann(input_shape=(32 * 32 * 3,), no_classes=10, hidden_layers=(128,)):
    inputs = Input(shape=input_shape)
    x = create_dense_layer(hidden_layers[0])(inputs)
    for no_units in hidden_layers[1:]:
        x = create_dense_layer(no_units)(x)
    x = create_dense_layer(no_classes)(x)
    return K.Model(inputs=inputs, outputs=x, name='cifar10_ann')


def create_cnn(input_shape=(32, 32, 3), no_classes=10, filter_stride_pairs=((128, 1),)):
    inputs = Input(shape=input_shape)
    x = create_conv_layer(*filter_stride_pairs[0])(inputs)
    for filters, strides in filter_stride_pairs[1:]:
        x = create_conv_layer(filters, strides)(x)
        x = BatchNormalization()(x)
    x = create_conv_layer(no_classes, kernel_size=1)(x)
    x = GlobalAvgPool2D()(x)
    return K.Model(inputs=inputs, outputs=x, name='cifar10_cnn')


if __name__ == '__main__':
    model = create_ann(hidden_layers=(512, 128, 64))
    model.summary()
    model = create_cnn(filter_stride_pairs=(
        (16, 1),
        (32, 1),
        (32, 1),
        (64, 2),
        (64, 1),
        (128, 1),
        (128, 1),
        (256, 2),
        (256, 1),
        (256, 1),
        #(256, 1)
    ))
    model.summary()
