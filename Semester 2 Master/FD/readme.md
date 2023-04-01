# Tensorflow and Keras framework proof of concept

## Introduction

TensorFlow and Keras are popular open-source machine learning frameworks widely
used in building and training deep learning models.

TensorFlow is an end-to-end open-source platform for building machine learning
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


## Dataset

