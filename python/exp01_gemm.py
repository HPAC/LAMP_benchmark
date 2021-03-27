import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp01_gemm')

@benchmark
def gemm_implicit_noup(A, B, C):
    C = A @ B
    return C


def exp01_gemm(b, n):

    A = tf.random.normal([n, n])
    B = tf.random.normal([n, n])
    C = tf.random.normal([n, n])

    res = b.benchmark('gemm_implicit_noup', gemm_implicit_noup, A, B, C)
