import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp11_blocked_matrices')

@benchmark
def blocked_solve_naive(A1, A2, B, C):
    C = tf.linalg.solve(tf.concat(
        (tf.concat((A1, tf.zeros((A1.shape[0], A1.shape[1]), dtype=tf.float64)), 1),
         tf.concat((tf.zeros((A2.shape[0], A2.shape[1]), dtype=tf.float64), A2), 1)), 0), B)
    return C

@benchmark
def blocked_solve_recommended(A1, A2, B, C):
    b1 = B[0:A1.shape[0], 0:B.shape[1]]
    b2 = B[A1.shape[0]:, 0:B.shape[1]]
    C = tf.concat((tf.linalg.solve(A1, b1), tf.linalg.solve(A2, b2)), 0)
    return C

def exp11_blocked_matrices(b, n):

    bm_n = int(n / 2)
    A1 = tf.random.normal([bm_n, bm_n], dtype=tf.float64)
    A2 = tf.random.normal([bm_n, bm_n], dtype=tf.float64)
    B = tf.random.normal([2 * bm_n, 2 * bm_n], dtype=tf.float64)
    C = tf.zeros((2 * bm_n, 2 * bm_n), dtype=tf.float64)

    res1 = b.benchmark("compact", blocked_solve_naive, A1, A2, B, C)
    res2 = b.benchmark("blocked", blocked_solve_recommended, A1, A2, B, C)
    logger.info('PartitionedMatrices correctness: {}'.format(tf.experimental.numpy.allclose(res1, res2)))
