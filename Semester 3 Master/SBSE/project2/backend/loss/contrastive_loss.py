import tensorflow as tf


class ContrastiveLoss:
    def __init__(self, tau):
        self.tau = tau

    def __call__(self, positive_similarity, negative_similarity):
        scaled_positive_similarity = tf.math.exp(positive_similarity / self.tau)
        scaled_negative_similarity = tf.math.exp(negative_similarity / self.tau)
        return tf.reduce_sum(
            -tf.math.log(
                scaled_positive_similarity / (scaled_positive_similarity + scaled_negative_similarity)
            )
        ) / len(positive_similarity)
