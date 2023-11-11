from overrides import overrides
from backend.trainer.generic_trainer import GenericTrainer
import tensorflow as tf


class ContrastiveTrainer(GenericTrainer):
    def compute_similarities(self, inputs):
        original, duplicate, not_duplicate = inputs

        positive_similarity = self.model([original, duplicate])
        negative_similarity = self.model([original, not_duplicate])

        return positive_similarity, negative_similarity

    @overrides
    def compute_loss(self, inputs):
        return self.loss(*self.compute_similarities(inputs))

    @overrides
    def forward(self, inputs):
        return tf.concat(self.compute_similarities(inputs), axis=1)
