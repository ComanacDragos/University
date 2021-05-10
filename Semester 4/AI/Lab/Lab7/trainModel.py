import time

from createdb import Database
from myModel import Net
from settings import *
from utils import *


class TrainModel:
    def __init__(self, file='myNet.pt', device=DEVICE):
        self._device = torch.device(device)

        self._file = file
        self._db = Database()
        self._db.load()
        self._loss_function = torch.nn.MSELoss()
        self._ann = Net().to(device)
        print(self._ann)
        self._optimizer_batch = torch.optim.SGD(self._ann.parameters(), lr=LEARNING_RATE)

        self.loss_list = None
        self.averages = []

        self._train_inputs = []
        self._train_outputs = []
        self._validation_inputs = []
        self._validation_outputs = []
        self.split_data()

        self._n_batches = int(len(self._train_inputs) / BATCH_SIZE)

        # self._train_inputs = self._db.data_set.to(device)
        # self._train_outputs = torch.tensor([[sinFunction(*point)] for point in self._db.data_set]).to(device)

    @property
    def ann(self):
        return self._ann

    def split_data(self):
        inputs = self._db.data_set

        split = [int(len(inputs) * TRAIN_VALIDATION_SPLIT), len(inputs) - int(len(inputs) * TRAIN_VALIDATION_SPLIT)]
        self._train_inputs, self._validation_inputs = torch.split(inputs, split)

        self._train_outputs = torch.tensor([[sinFunction(*point)] for point in self._train_inputs]).to(self._device)
        self._validation_outputs = torch.tensor([[sinFunction(*point)] for point in self._validation_inputs]).to(self._device)

        self._train_inputs = self._train_inputs.to(self._device)
        self._validation_inputs = self._validation_inputs.to(self._device)

        # print(len(inputs))
        # print(len(self._train_inputs), len(self._train_outputs))
        # print(len(self._validation_inputs), len(self._validation_outputs))

    def train(self):
        totalTime = 0
        for epoch in range(EPOCHS):
            batch_start = time.time()
            self.loss_list = []
            for batch in range(self._n_batches):
                batch_in, batch_out = self._train_inputs[batch * BATCH_SIZE:(batch + 1) * BATCH_SIZE], \
                                      self._train_outputs[batch * BATCH_SIZE:(batch + 1) * BATCH_SIZE]
                prediction = self._ann(batch_in)

                loss = self._loss_function(prediction, batch_out)

                self.loss_list.append(loss)
                self._optimizer_batch.zero_grad()
                loss.backward()
                self._optimizer_batch.step()

            batch_time = time.time() - batch_start
            totalTime += batch_time
            self.averages.append(torch.mean(torch.tensor(self.loss_list), dtype=torch.float64))

            if epoch % 100 == 0 or epoch == EPOCHS - 1:
                y_pred = self._ann(self._validation_inputs)
                loss = self._loss_function(y_pred, self._validation_outputs)
                print(f"Epoch: {epoch}\tLoss= {loss} {totalTime}")
                totalTime = 0

        if SAVE_MODEL:
            torch.save(self._ann.state_dict(), self._file)

"""
for epoch, loss in enumerate(train.loss_list):
    print(f"Epoch: {epoch}\tLoss= {loss}")
# print(train._ann.state_dict())
# torch.cuda.current_device()
# torch.cuda.device_count()

db = Database()
db.load()



#device = torch.device("cuda:0")
device = torch.device("cpu")
x = db.data_set.to(device)
y = torch.tensor([[sinFunction(*point)] for point in x]).to(device)

lossFunction = torch.nn.MSELoss()

# we create the ANN
ann = Net().to(device)

print(all(p.is_cuda for p in ann.parameters()))

print(ann)
# we use an optimizer that implements stochastic gradient descent
optimizer_batch = torch.optim.SGD(ann.parameters(), lr=0.01)

# we memorize the losses forsome graphics
loss_list = []
avg_loss_list = []

# we set up the environment for training in batches
batch_size = 16
n_batches = int(len(x) / batch_size)
print(n_batches)

start = time.time()
for epoch in range(2000):
    for batch in range(n_batches):
        # we prepare the current batch  -- please observe the slicing for tensors
        batch_X, batch_y = x[batch * batch_size:(batch + 1) * batch_size, ], \
                           y[batch * batch_size:(batch + 1) * batch_size, ]
        # we compute the output for this batch
        prediction = ann(batch_X)

        # we compute the loss for this batch
        loss = lossFunction(prediction, batch_y)

        # we save it for graphics
        loss_list.append(loss)

        # we set up the gradients for the weights to zero (important in pytorch)
        optimizer_batch.zero_grad()

        # we compute automatically the variation for each weight (and bias) of the network
        loss.backward()

        # we compute the new values for the weights
        optimizer_batch.step()

        # we print the loss for all the dataset for each 10th epoch
    if epoch % 100 == 99:
        y_pred = ann(x)
        loss = lossFunction(y_pred, y)
        print('\repoch: {}\tLoss =  {:.5f}'.format(epoch, loss))


print(time.time() - start)
"""