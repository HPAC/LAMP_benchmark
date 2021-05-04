import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp02_syrk')


@benchmark
def syrk_implicit_noup(A, C):
    C = A @ tf.transpose(A)
    return C


def exp02_syrk(b, n):
    A = tf.random.normal([n, n], dtype=tf.float64)
    C = tf.random.normal([n, n], dtype=tf.float64)
    C = C + tf.transpose(C)

    res = b.benchmark('syrk_implicit_noup', syrk_implicit_noup, A, C)
