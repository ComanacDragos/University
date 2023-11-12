from config.common.resnet_backbone_config import ResnetBackboneConfig
from backend.model.contrastive_model import ContrastiveModel, ContrastiveHead
from tensorflow.keras.layers import Conv1D, Input
from tensorflow.keras.models import Model
from backend.utils import logger
import tensorflow.keras.backend as K


def cosine_similarity(x, y):
    x = K.l2_normalize(x, axis=-1)
    y = K.l2_normalize(y, axis=-1)
    sim = -K.sum(x * y, axis=-1, keepdims=True)
    return 1 - ((sim + 1) / 2)  # convert to 0, 1 where 1 means similar


class ContrastiveModelConfig:
    @staticmethod
    def build(input_shape):
        inputs = [Input(input_shape), Input(input_shape)]
        x = ContrastiveModel(
            similarity_function=cosine_similarity,
            backbone=ResnetBackboneConfig.build(Conv1D),
            head=ContrastiveHead()
        )(inputs)
        model = Model(inputs=inputs, outputs=x, name='DuplicateCodeClassifier')
        model.summary(print_fn=logger)
        return model


if __name__ == '__main__':
    ContrastiveModelConfig.build((65, 1024)).summary()

    # x = [[0., 1.], [1., 1.]]
    # y = [[1., 0.], [0., 0.]]
    #
    # print(cosine_similarity(x, y))
    #
    # x = [[0., 1.], [1., 1.]]
    # y = [[1., 0.], [1., 1.]]
    #
    # print(cosine_similarity(x, y))
    #
    # x = [[0., 1.], [1., 1.]]
    # y = [[0., 1.], [1., 1.]]
    #
    # print(cosine_similarity(x, y))
