import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp03_syr2k')

@benchmark
def syr2k_implicit_noup(A, B, C):
    C = A @ tf.transpose(B) + B @ tf.transpose(A)
    return C


def exp03_syr2k(b, n):

    A = tf.random.normal([n, n], dtype=tf.float64)
    B = tf.random.normal([n, n], dtype=tf.float64)
    C = tf.random.normal([n, n], dtype=tf.float64)
    C = C + tf.transpose(C)

    res = b.benchmark('syr2k_implicit_noup', syr2k_implicit_noup, A, B, C)
