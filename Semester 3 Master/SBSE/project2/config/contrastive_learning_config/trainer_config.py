from backend.trainer import ContrastiveTrainer
from loss_config import ContrastiveLossConfig
from data_generator_config import MethodDataGeneratorConfig
from config.common.callbacks_config import CallbacksConfig
from model_config import ContrastiveModelConfig
from backend.enums import Stage
from backend.utils import set_seed
import shutil
from tensorflow.keras.optimizers import Adam
from pathlib import Path


class ContrastiveTrainerConfig:
    EXPERIMENT = Path('output/test_train')

    EPOCHS = 10
    START_LR = 1e-4

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
    set_seed(0)
    shutil.copytree('config', ContrastiveTrainerConfig.EXPERIMENT / 'config', dirs_exist_ok=True)
    ContrastiveTrainerConfig.build().train()
