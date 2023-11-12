from backend.callbacks.LoggableCallback import LoggableCallback
from backend.trainer.state import TrainState
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import host_subplot
import mpl_toolkits.axisartist as AA


class LossLogger(LoggableCallback):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self._create_csv(self.csv_path, ['epoch', 'step', 'lr', 'loss'])

    def on_train_batch_end(self, batch, logs: TrainState = None):
        csv = pd.read_csv(self.csv_path)
        csv.loc[len(csv)] = [
            logs.epoch,
            batch,
            logs.optimizer.get_config()['learning_rate'],
            logs.loss
        ]
        losses = [round(x, 9) for x in csv.loc[:, 'loss']]
        lrs = [round(x, 9) for x in csv.loc[:, 'lr']]
        epochs = [int(x) for x in csv.loc[:, 'epoch']]
        self.plot_loss(losses, lrs, epochs)
        csv.to_csv(
            self.csv_path, index=False,
            float_format=lambda x: round(x, 9)
        )

    def plot_loss(self, losses, lrs, epochs):
        loss_plot = host_subplot(111, axes_class=AA.Axes)
        plt.subplots_adjust(right=0.75)
        learning_rate_plot = loss_plot.twinx()

        new_fixed_axis = learning_rate_plot.get_grid_helper().new_fixed_axis
        learning_rate_plot.axis['right'] = new_fixed_axis(
            loc='right',
            axes=learning_rate_plot
        )

        learning_rate_plot.axis['right'].toggle(all=True)

        loss_plot.set_xlabel('Epoch')
        loss_plot.set_ylabel('Loss')

        learning_rate_plot.set_ylabel('Learning rate')

        steps = list(range(len(losses)))

        first_plot, = loss_plot.plot(steps, losses, label='Loss')
        second_plot, = learning_rate_plot.plot(steps, lrs, label='LR')

        loss_plot.legend()

        loss_plot.axis['left'].label.set_color(first_plot.get_color())
        learning_rate_plot.axis['right'].label.set_color(second_plot.get_color())

        x_labels = [str(x) for x in set(epochs)]
        x_ticks = [0] + [i for i in range(1, len(epochs)) if epochs[i] != epochs[i - 1]]
        plt.xticks(x_ticks, x_labels)

        plt.draw()
        plt.savefig(self.output_path / 'loss.png')
        plt.clf()
