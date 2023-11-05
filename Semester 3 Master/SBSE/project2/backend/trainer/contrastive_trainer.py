import tensorflow as tf


class ContrastiveTrainer:
    def __init__(
            self,
            train_dataset,
            val_dataset,
            loss,
            similarity_function,
            optimizer,
            callbacks,
            model,
            epochs
    ):
        self.train_dataset = train_dataset
        self.val_dataset = val_dataset
        self.loss = loss
        self.similarity_function = similarity_function
        self.optimizer = optimizer
        self.callbacks = callbacks
        self.model = model
        self.epochs = epochs

    def train(self):
        self.model.compile(self.optimizer)
        for epoch in range(self.epochs):
            print(f"Epoch {epoch}")
            self.train_loop()
            self.eval_loop()

    def train_loop(self):
        for step, (original, duplicate, not_duplicate) in enumerate(self.train_dataset):
            with tf.GradientTape() as tape:
                original_representation = self.model(original)
                duplicate_representation = self.model(duplicate)
                not_duplicate_representation = self.model(not_duplicate)

                positive_similarity = self.similarity_function(original_representation, duplicate_representation)
                negative_similarity = self.similarity_function(original_representation, not_duplicate_representation)

                loss_value = self.loss(positive_similarity, negative_similarity)

            grads = tape.gradient(loss_value, self.model.tranable_weights)
            self.optimizer.apply_gradients(zip(grads, self.model.trainable_weights))
            if step % 200 == 0:
                print(
                    "Training loss (for one batch) at step %d: %.4f"
                    % (step, float(loss_value))
                )
                print("Seen so far: %s samples" % ((step + 1) * self.train_dataset.batch_size))

    def eval_loop(self):
        pass
