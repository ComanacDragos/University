import tensorflow.keras as K
from tensorflow.keras.layers import Input, Dense, Conv1D, BatchNormalization, GlobalAvgPool1D


def create_dense_layer(output_units):
    return Dense(output_units,
                 activation='relu',
                 kernel_initializer=K.initializers.HeNormal(),
                 kernel_regularizer=K.regularizers.l2()
                 )


def create_conv_layer(filters, strides=1, kernel_size=3):
    return Conv1D(filters,
                  kernel_size=kernel_size,
                  padding='same',
                  strides=strides,
                  activation='relu',
                  kernel_initializer=K.initializers.HeNormal(),
                  kernel_regularizer=K.regularizers.l2()
            )


def create_cnn(input_shape, no_classes, filter_stride_pairs=((128, 1),)):
    inputs = Input(shape=input_shape)
    x = create_conv_layer(*filter_stride_pairs[0])(inputs)
    x = BatchNormalization()(x)
    for filters, strides in filter_stride_pairs[1:]:
        x = create_conv_layer(filters, strides)(x)
        x = BatchNormalization()(x)
    x = create_conv_layer(no_classes, kernel_size=1)(x)
    x = GlobalAvgPool1D()(x)
    return K.Model(inputs=inputs, outputs=x, name='cnn')


if __name__ == '__main__':
    model = create_cnn(input_shape=(70, 1014), no_classes=4, filter_stride_pairs=(
        (16, 1),
        (32, 1),
        (32, 1),
        (64, 2),
        (64, 1),
        (128, 1),
        (128, 1),
        (256, 2),
        (256, 1),
        (256, 1)
    ))
    model.summary()
