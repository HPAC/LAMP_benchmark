import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp05_explicit_inversion')

@benchmark
def solve_nai(A, B):
    C = tf.linalg.inv(A) @ B
    return C

@benchmark
def solve_rec(A, B):
    C = tf.linalg.solve(A, B)
    return C


def exp05_explicit_inversion(b, n):

    A = tf.random.normal([n, n], dtype=tf.float64)
    B = tf.random.normal([n, 200], dtype=tf.float64)

    res1 = b.benchmark('solve_nai', solve_nai, A, B)
    res2 = b.benchmark('solve_rec', solve_rec, A, B)
    logger.info('Solve correctness: {}'.format(tf.debugging.assert_near(res1, res2, rtol=1e-05, atol=1e-08)))

    B = tf.random.normal([n, 5*n], dtype=tf.float64)  # B.rows , 5 * A.rows
    res3 = b.benchmark('solve_large_nai', solve_nai, A, B)
    res4 = b.benchmark('solve_large_rec', solve_rec, A, B)
    logger.info('Solve correctness: {}'.format(tf.debugging.assert_near(res3, res4, rtol=1e-05, atol=1e-08)))
