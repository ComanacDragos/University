from overrides import overrides
from generic_trainer import GenericTrainer


class ContrastiveTrainer(GenericTrainer):
    @overrides
    def compute_loss(self, inputs):
        original, duplicate, not_duplicate = inputs
        original_representation = self.model(original)
        duplicate_representation = self.model(duplicate)
        not_duplicate_representation = self.model(not_duplicate)

        positive_similarity = self.similarity_function(original_representation, duplicate_representation)
        negative_similarity = self.similarity_function(original_representation, not_duplicate_representation)

        loss_value = self.loss(positive_similarity, negative_similarity)
        return loss_value
