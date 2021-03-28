from benchmarker import benchmark
import logging
import tensorflow as tf

logger = logging.getLogger('exp07_properties_multiplication')

@benchmark
def trmm_implicit(A, B):
    B = A @ B
    return B

@benchmark
def diagmm(A, B, C):
    C = A @ B
    return C


def exp07_properties_multiplication(b, n):

    A = tf.random.normal([n, n])
    B = tf.random.normal([n, n])
    C = tf.random.normal([n, n])

    A = tf.experimental.numpy.tril(A)
    logger.debug('A is triangualar'.format(tf.experimental.numpy.allclose(A, tf.experimental.numpy.tril(A))))
    res1 = b.benchmark('trmm_implicit', trmm_implicit, A, B)

    Ad = tf.experimental.numpy.diag(tf.experimental.numpy.diag(A))
    res2 = b.benchmark('diagmm', diagmm, Ad, B, C)
