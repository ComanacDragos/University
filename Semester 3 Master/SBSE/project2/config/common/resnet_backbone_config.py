from backend.model.blocks import ConvBlock
from backend.model.generic_model import GenericBackbone
from tensorflow.keras.layers import LeakyReLU, BatchNormalization, Dropout
from tensorflow.keras.initializers import HeNormal
from tensorflow.keras.regularizers import l1_l2


class ResnetBackboneConfig:

    @staticmethod
    def build(conv_type):
        def activation_generator():
            return LeakyReLU(alpha=0.1)

        def dropout_generator():
            return Dropout(rate=0.2)

        def batch_norm_generator():
            return BatchNormalization()

        def conv_generator(kernel_size, filters, strides):
            return lambda: conv_type(
                kernel_size=kernel_size,
                filters=filters,
                padding='same',
                strides=strides,
                kernel_initializer=HeNormal(),
                kernel_regularizer=l1_l2(l1=1e-6, l2=1e-5)
            )

        def block_generator(kernel_size=3, filters=32, strides=1, skip_connection_size=0):
            return ConvBlock(
                conv_generator(kernel_size, filters, strides),
                skip_connection_size=skip_connection_size,
                activation_generator=activation_generator,
                dropout_generator=dropout_generator,
                batch_norm_generator=batch_norm_generator,
            )

        return GenericBackbone(blocks=[
            block_generator(filters=512),
            block_generator(filters=256),
            block_generator(filters=256, skip_connection_size=2),
            block_generator(filters=128),
            block_generator(filters=128, skip_connection_size=2),
            block_generator(filters=64),
            block_generator(filters=64, skip_connection_size=2),
            block_generator(filters=32),
        ])
