# Tensorflow and Keras framework proof of concept

## Introduction

TensorFlow and Keras are popular open-source machine learning frameworks widely
used in building and training deep learning models.

TensorFlow is an open-source platform for building machine learning
and deep learning models. It provides a set of libraries for data manipulation,
preprocessing, and visualization, along with a high-level API to build
and train deep neural networks.
TensorFlow is highly scalable and can be used to train models on a single machine
or distributed across multiple servers or GPUs.

Keras, on the other hand, is a high-level API for building and training 
deep learning models. 
It is built on top of TensorFlow and provides a user-friendly interface
for building complex deep learning models quickly. 
Keras abstracts away many of the low-level details of TensorFlow,
making it easier for beginners to get started with deep learning. 
Keras includes a wide range of pre-built layers and models, 
making it easier to construct complex neural networks.

TensorFlow and Keras are important because they simplify the 
development and training of deep learning models, which can be complex and
time-consuming. They provide a high-level API for building neural networks, 
allowing developers to focus on the model's architecture and not on the 
implementation details. TensorFlow and Keras also provide tools for model 
visualization, making it easier to understand the model's performance and 
make improvements. 

## Setup

The setup is pretty straight-forward. Firstly, a virtual environment needs to be
created and activated, for instance with Anaconda:

```
conda create -n ENV_NAME python=3.8
conda activate ENV_NAME
```

Afterwards, we can install tensorflow with pip:

```
pip3 install --upgrade tensorflow==2.3.0
```

This step can be done also with a local interpreter, not necessarily
in an Anaconda environment.

After this, tensorflow and keras can be loaded as follows:

```python
import tensorflow.keras as K
import tensorflow as tf
```


## Dataset

Tensorflow offers many built in datasets. We will use MNIST which is composed
of grayscale images that depict digits, and it can be loaded as follows:

```python
data = tf.keras.datasets.mnist
(X_train, Y_train), (X_test, Y_test) = data.load_data()
```

Also, custom datasets can be defined.

The next step is to preprocess the data:

```python
def process_data(X):
    X = K.utils.normalize(X)
    X = tf.expand_dims(X, axis=-1)
    return X
```

In the function above, X represents the tensor with the images, and the
first step is to normalize the image and then an extra dimension (channel dimension)
is added. The function is called as follows:

```python
X_train = process_data(X_train)
X_test = process_data(X_test)
```

The normalization is optional, but it helps the learning, and adding an
extra channel dimension is necessary when using convolutions.   

## Model

The next step is defining the model. The functional way of defining it in our case is
the following:

```python
def createModel(input_shape, num_classes, optimizer, loss, metrics):
    inputs = K.layers.Input(input_shape)
    x = K.layers.Conv2D(filters=64, kernel_size=(3, 3), activation='relu')(inputs)
    x = K.layers.Conv2D(filters=128, kernel_size=(3, 3), padding="same", activation='relu')(x)
    x = K.layers.MaxPool2D()(x)
    x = K.layers.Conv2D(filters=256, kernel_size=(3, 3), padding="same", activation='relu')(x)
    x = K.layers.MaxPool2D()(x)
    x = K.layers.Flatten()(x)
    x = K.layers.Dense(num_classes, activation='softmax')(x)

    model = K.models.Model(inputs=inputs, outputs=x)
    model.compile(optimizer=optimizer, loss=loss, metrics=[metrics])
    return model

model = createModel(input_shape=(28, 28, 1), num_classes=10, optimizer='adam',
                    loss='sparse_categorical_crossentropy',
                    metrics='accuracy')
```

There are several layers used, such as Conv2d, MaxPool2d or Dense, and 
Keras offers many more, depending on the problem.

The first stage is defining the structure of the model, then it needs to
be compiled with the optimizer, loss and metrics. In our case, the loss
is sparse because the labels are provided as integers.

The exact structure can be seen ass follows:

```python
model.summary()
```

Which outputs:
```
Model: "functional_1"
_________________________________________________________________
Layer (type)                 Output Shape              Param #   
=================================================================
input_1 (InputLayer)         [(None, 28, 28, 1)]       0         
_________________________________________________________________
conv2d (Conv2D)              (None, 26, 26, 64)        640       
_________________________________________________________________
conv2d_1 (Conv2D)            (None, 26, 26, 128)       73856     
_________________________________________________________________
max_pooling2d (MaxPooling2D) (None, 13, 13, 128)       0         
_________________________________________________________________
conv2d_2 (Conv2D)            (None, 13, 13, 256)       295168    
_________________________________________________________________
max_pooling2d_1 (MaxPooling2 (None, 6, 6, 256)         0         
_________________________________________________________________
flatten (Flatten)            (None, 9216)              0         
_________________________________________________________________
dense (Dense)                (None, 10)                92170     
=================================================================
Total params: 461,834
Trainable params: 461,834
Non-trainable params: 0
_________________________________________________________________
```

This is useful because we can see the exact number of parameters for each
layer.

## Training

The training process is quite straightforward, because tensorflow hides 
the complex mathematical computations behind the scenes. It is enough
to use the following:

```python
model.fit(X_train, Y_train, epochs=3, batch_size=256, validation_split=0.2)
```

And in order to save the model after training:

```python
model.save("model")
```

Afterwards, the model can be loaded as such:

```python
model = K.models.load_model('model')
```

## Testing

After training, it might be desirable to see the performance on a separate
part of the dataset, which has not been used in training, and it is usually
called "test set" and it can be done using one line:

```python
results = model.evaluate(X_test, Y_test, batch_size=256)
```

Before doing this, the model needs to be loaded and compiled with the
desired metric:

```python
model = K.models.load_model('model')
model.compile(metrics='accuracy')
```

## Inference

Another important aspect is the inference. This basically consists of
giving the model some specific inputs and see the results. For instance,
we can generate some random indexes and select the data at those indexes:

```python
idxs = np.random.randint(0, len(X_test), size=(9,))

X_test = tf.gather(X_test, idxs)
Y_test = tf.gather(Y_test, idxs)
```

Afterwards we can get the predicted probabilities out of which the digits
can be extracted:

```python
predicted_probabilities = model(X_test)
predicted_digits = tf.argmax(predicted_probabilities, axis=-1)
```

![image](https://user-images.githubusercontent.com/46956225/229370141-cfce2898-fb50-4430-8a8d-56fcc98e1e5c.png)
