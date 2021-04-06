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

    A = tf.random.normal([n, n], dtype=tf.float64)
    B = tf.random.normal([n, n], dtype=tf.float64)
    C = tf.random.normal([n, n], dtype=tf.float64)

    A = tf.linalg.band_part(A, -1, 0)
    logger.debug('A is triangualar'.format(tf.debugging.assert_near(A, tf.linalg.band_part(A, -1, 0), rtol=1e-05, atol=1e-08)))
    res1 = b.benchmark('trmm_implicit', trmm_implicit, A, B)

    Ad = tf.linalg.diag(tf.linalg.diag_part(A))
    res2 = b.benchmark('diagmm', diagmm, Ad, B, C)
