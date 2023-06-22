import tensorflow.keras as K
from tensorflow.keras.layers import Input, Dense, Conv1D, BatchNormalization, GlobalAvgPool1D, Flatten, Dropout, \
    MaxPool1D, Add, ReLU
from tensorflow.python.keras.utils.vis_utils import plot_model


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
                  activation=K.activations.relu,
                  kernel_initializer=K.initializers.HeNormal(),
                  kernel_regularizer=K.regularizers.l2()
            )


def fully_conv(input_shape, no_classes, filter_stride_pairs=((128, 1),)):
    inputs = Input(shape=input_shape)
    x = create_conv_layer(*filter_stride_pairs[0])(inputs)
    x = BatchNormalization()(x)
    for filters, strides in filter_stride_pairs[1:]:
        x = create_conv_layer(filters, strides)(x)
        x = BatchNormalization()(x)
    x = create_conv_layer(no_classes, kernel_size=1)(x)
    x = GlobalAvgPool1D()(x)
    return K.Model(inputs=inputs, outputs=x, name='cnn_fully_conv')


def original(input_shape, no_classes, filters, out_units):
    inputs = Input(shape=input_shape)
    x = create_conv_layer(filters, kernel_size=7)(inputs)
    x = MaxPool1D(pool_size=3)(x)
    x = create_conv_layer(filters, kernel_size=7)(x)
    x = create_conv_layer(filters)(x)
    x = MaxPool1D(pool_size=3)(x)
    x = create_conv_layer(filters)(x)
    x = create_conv_layer(filters)(x)
    x = create_conv_layer(filters)(x)
    x = MaxPool1D(pool_size=3)(x)
    x = Flatten()(x)

    x = create_dense_layer(out_units)(x)
    x = Dropout(0.5)(x)
    x = create_dense_layer(out_units)(x)
    x = Dropout(0.5)(x)
    x = create_dense_layer(no_classes)(x)

    return K.Model(inputs=inputs, outputs=x, name='cnn_original')


def resnet_block(x, filters):
    inputs = x
    x = create_conv_layer(filters)(x)
    x = BatchNormalization()(x)
    x = create_conv_layer(filters)(x)
    x = BatchNormalization()(x)
    x = Add()([x, inputs])
    x = BatchNormalization()(x)
    x = ReLU()(x)
    return x


def resnet(input_shape, no_classes, filter_stride_pairs=((128, 1),)):
    inputs = Input(shape=input_shape)
    x = create_conv_layer(*filter_stride_pairs[0])(inputs)
    x = BatchNormalization()(x)
    x = Dropout(0.5)(x)
    last_filters = filter_stride_pairs[0][0]
    count = 0
    for filters, strides in filter_stride_pairs[1:]:
        if strides != 1 or last_filters != filters:
            x = create_conv_layer(filters, strides)(x)
            x = BatchNormalization()(x)
        else:
            x = resnet_block(x, filters)
        last_filters = filters
        if count > 0:
            count -= 1
            x = Dropout(0.3)(x)

    x = create_conv_layer(no_classes, kernel_size=1)(x)
    x = GlobalAvgPool1D()(x)
    return K.Model(inputs=inputs, outputs=x, name='cnn_resnet')


def custom(input_shape, no_classes):
    inputs = Input(shape=input_shape)
    x = create_conv_layer(512)(inputs)
    x = create_conv_layer(no_classes, kernel_size=1)(x)
    x = GlobalAvgPool1D()(x)
    return K.Model(inputs=inputs, outputs=x, name='cnn_resnet')


def create_cnn(input_shape, no_classes, model_type):
    if model_type == "original":
        return original(input_shape, no_classes, 1024, 2048)
    elif model_type == 'custom':
        return custom(input_shape, no_classes)
    elif model_type == 'resnet':
        return resnet(input_shape, no_classes, filter_stride_pairs=(
            (1024, 1),
            (512, 1),
            (512, 1),
            (256, 2),
            (256, 1),
            (128, 2),
            (128, 1),
            (64, 2),
            (64, 1),
            (32, 2),
            (32, 1),
            (16, 2),
            (16, 1),
        ))
    elif model_type == "fully_conv":
        return fully_conv(input_shape, no_classes, filter_stride_pairs=(
            # (16, 1),
            # (32, 1),
            # (32, 1),
            # (64, 2),
            # (64, 1),
            # (128, 1),
            # (128, 1),
            (256, 2),
            (256, 1),
            (256, 1),
        ))
    else:
        raise "Bad model type"


if __name__ == '__main__':
    model = create_cnn(input_shape=(70, 1014), no_classes=4, model_type='resnet')
    model.summary()
    plot_model(model, show_shapes=True, show_layer_names=True)
