from abc import abstractmethod

import tensorflow as tf
from tensorflow.keras.callbacks import CallbackList
from state import TrainState, EvalState


class GenericTrainer:
    def __init__(
            self,
            train_dataset,
            val_dataset,
            loss,
            similarity_function,
            optimizer,
            callbacks: CallbackList,
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

        self.callbacks.on_train_begin()
        for epoch in range(self.epochs):
            self.callbacks.on_epoch_begin(epoch)
            self.train_loop(epoch)
            self.eval_loop(epoch)
            self.callbacks.on_epoch_end(epoch)
        self.callbacks.on_train_end()

    @abstractmethod
    def compute_loss(self, inputs):
        samples, labels = inputs
        predictions = self.model(samples)
        loss = self.loss(predictions, labels)
        return loss

    def train_loop(self, epoch):
        for step, inputs in enumerate(self.train_dataset):
            self.callbacks.on_train_batch_begin(step)
            with tf.GradientTape() as tape:
                loss_value = self.compute_loss(inputs)

            grads = tape.gradient(loss_value, self.model.trainable_weights)
            self.optimizer.apply_gradients(zip(grads, self.model.trainable_weights))
            # if step % 200 == 0:
            print(
                "Training loss (for one batch) at step %d: %.4f"
                % (step, float(loss_value))
            )
            # print("Seen so far: %s samples" % ((step + 1) * self.train_dataset.batch_size))

            self.callbacks.on_train_batch_end(step)

    def eval_loop(self, epoch):
        pass
