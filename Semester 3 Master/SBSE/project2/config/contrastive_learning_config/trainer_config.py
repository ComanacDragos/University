from backend.trainer import ContrastiveTrainer
from loss_config import ContrastiveLossConfig
from data_generator_config import MethodDataGeneratorConfig
from config.common.callbacks_config import CallbacksConfig
from model_config import ModelConfig
from backend.enums import Stage
import tensorflow.keras.backend as K
from tensorflow.keras.optimizers import Adam


def cosine_similarity(x, y):
    x = K.l2_normalize(x, axis=-1)
    y = K.l2_normalize(y, axis=-1)
    sim = -K.sum(x * y, axis=-1, keepdims=True)
    return 1 - ((sim + 1) / 2)  # convert to 0, 1 where 1 means similar


class ContrastiveTrainerConfig:
    EXPERIMENT = 'output/first_train'

    EPOCHS = 10
    START_LR = 1e-3

    @staticmethod
    def build():
        input_shape = (len(MethodDataGeneratorConfig.ALPHABET), MethodDataGeneratorConfig.MAX_LENGTH)
        return ContrastiveTrainer(
            MethodDataGeneratorConfig.build(Stage.TRAIN),
            MethodDataGeneratorConfig.build(Stage.VAL),
            ContrastiveLossConfig.build(),
            cosine_similarity,
            Adam(learning_rate=ContrastiveTrainerConfig.START_LR),
            CallbacksConfig.build(),
            ModelConfig.build(input_shape),
            ContrastiveTrainerConfig.EPOCHS
        )


if __name__ == '__main__':
    ContrastiveTrainerConfig.build().train()
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
