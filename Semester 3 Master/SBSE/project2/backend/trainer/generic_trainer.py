import tensorflow as tf
from tensorflow.keras.callbacks import CallbackList
from backend.trainer.state import TrainState, EvalState
from tqdm import tqdm
from backend.utils import logger


class GenericTrainer:
    def __init__(
            self,
            train_dataset,
            val_dataset,
            loss,
            optimizer,
            callbacks: CallbackList,
            model,
            epochs
    ):
        self.train_dataset = train_dataset
        self.val_dataset = val_dataset
        self.loss = loss
        self.optimizer = optimizer
        self.callbacks = callbacks
        self.model = model
        self.epochs = epochs

    def train(self):
        self.model.compile(self.optimizer)

        self.callbacks.on_train_begin()
        for epoch in range(self.epochs):
            logger.log(f"\nTrain epoch {epoch}")
            self.callbacks.on_epoch_begin(epoch)
            self.train_loop(epoch)
            logger.log(f"\nEval epoch {epoch}")
            self.eval_loop(epoch)
            self.callbacks.on_epoch_end(epoch)
        self.callbacks.on_train_end()

    def compute_loss(self, inputs):
        samples, labels = inputs
        loss = self.loss(self.forward(inputs), labels)
        return loss

    def forward(self, inputs):
        samples, _ = inputs
        predictions = self.model(samples)
        return predictions

    def train_loop(self, epoch):
        for step, inputs in tqdm(enumerate(self.train_dataset), total=len(self.train_dataset), miniters=0):
            self.callbacks.on_train_batch_begin(
                step,
                logs=TrainState(
                    epoch=epoch,
                    inputs=inputs,
                    optimizer=self.optimizer,
                    model=self.model,
                )
            )
            with tf.GradientTape() as tape:
                loss_value = self.compute_loss(inputs)

            grads = tape.gradient(loss_value, self.model.trainable_weights)
            self.optimizer.apply_gradients(zip(grads, self.model.trainable_weights))
            self.callbacks.on_train_batch_end(
                step,
                logs=TrainState(
                    epoch=epoch,
                    inputs=inputs,
                    optimizer=self.optimizer,
                    model=self.model,
                    loss=loss_value.numpy()
                )
            )

    def eval_loop(self, epoch):
        all_predictions = []
        self.callbacks.on_predict_begin()
        for step, inputs in tqdm(enumerate(self.val_dataset), total=len(self.val_dataset), miniters=0):
            self.callbacks.on_predict_batch_begin(
                step,
                EvalState(epoch)
            )
            predictions = self.forward(inputs)
            all_predictions.append(predictions)
            self.callbacks.on_predict_batch_end(
                step,
                EvalState(
                    epoch,
                    predictions=predictions,
                    model=self.model
                )
            )
        self.callbacks.on_predict_end(
            logs=EvalState(
                epoch,
                predictions=tf.concat(all_predictions, axis=0),
                model=self.model
            )
        )
