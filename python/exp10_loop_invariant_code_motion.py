import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp10_loop_invariant_code_motion')

@benchmark
def naive_loop(A, B, c, temp):
    for i in range(c.shape[0]):
        temp = A @ B
        c = tf.tensor_scatter_nd_update(c, [[i]], [temp[i, i]])
    return c

@benchmark
def recommended_loop(A, B, c, temp):
    temp = A @ B
    for i in range(c.shape[0]):
        c = tf.tensor_scatter_nd_update(c, [[i]], [temp[i, i]])
    return c


def exp10_loop_invariant_code_motion(b, n):

    licm_n = int(n / 10)
    A = tf.random.normal([licm_n, licm_n], dtype=tf.float64)
    B = tf.random.normal([licm_n, licm_n], dtype=tf.float64)
    c = tf.random.normal([licm_n], dtype=tf.float64)
    temp = tf.zeros((licm_n, licm_n), dtype=tf.float64)

    res1 = b.benchmark("loop_nai", naive_loop, A, B, c, temp)
    res2 = b.benchmark("loop_rec", recommended_loop, A, B, c, temp)
    logger.info('LICM correctness: {}'.format(tf.debugging.assert_near(res1, res2, rtol=1e-05, atol=1e-08)))
