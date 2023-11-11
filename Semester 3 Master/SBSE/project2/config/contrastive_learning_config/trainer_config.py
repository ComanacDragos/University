from backend.trainer import ContrastiveTrainer
from loss_config import ContrastiveLossConfig
from data_generator_config import MethodDataGeneratorConfig
from config.common.callbacks_config import CallbacksConfig
from model_config import ContrastiveModelConfig
from backend.enums import Stage

from tensorflow.keras.optimizers import Adam


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
            Adam(learning_rate=ContrastiveTrainerConfig.START_LR),
            CallbacksConfig.build(ContrastiveTrainerConfig.EXPERIMENT),
            ContrastiveModelConfig.build(input_shape),
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
