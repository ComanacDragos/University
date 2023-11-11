from backend.model.generic_model import GenericModel
from tensorflow.keras.layers import GlobalAvgPool1D


class ContrastiveModel(GenericModel):
    def __init__(self, similarity_function, *args, **kwargs):
        self.similarity_function = similarity_function
        super().__init__(*args, **kwargs)

    def __call__(self, inputs):
        original, target = inputs
        original_representation = super().__call__(original)
        target_representation = super().__call__(target)

        return self.similarity_function(original_representation, target_representation)


class ContrastiveHead:
    def __call__(self, inputs):
        return GlobalAvgPool1D()(inputs)
