from config.common.resnet_backbone_config import ResnetBackboneConfig
from backend.model.generic import GenericModel
from tensorflow.keras.layers import Conv1D


class ModelConfig:
    @staticmethod
    def build():
        return GenericModel(
            backbone=ResnetBackboneConfig.build(Conv1D),
            head=lambda x: x,  # identity for now
            name="DuplicateCodeClassifier"
        )
