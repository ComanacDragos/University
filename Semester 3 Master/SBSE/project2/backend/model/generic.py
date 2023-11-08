from tensorflow.keras import Model
from tensorflow.keras.layers import Input


class GenericModel:
    def __init__(self, backbone, head, neck=None, name="model"):
        self.backbone = backbone
        self.neck = neck
        self.head = head
        self.name = name

    def __call__(self, input_shape):
        inputs = Input(input_shape)
        x = self.backbone(inputs)
        if self.neck:
            x = self.neck(x)
        x = self.head(x)
        return Model(inputs=inputs, outputs=x, name=self.name)


class GenericBackbone:
    def __init__(self, blocks):
        self.blocks = blocks

    def __call__(self, inputs):
        x = inputs
        for block in self.blocks:
            x = block(x)
        return x
