class TrainState:
    def __init__(self, epoch, inputs=None, optimizer=None, model=None, loss=None):
        self.epoch = epoch
        self.inputs = inputs
        self.optimizer = optimizer
        self.model = model
        self.loss = loss


class EvalState:
    def __init__(self, epoch, predictions=None):
        self.epoch = epoch
        self.predictions = predictions
