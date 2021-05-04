import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp09_common_subexpressions')


@benchmark
def subexpr_nai(A, B, K):
    K = A @ B + A @ B
    return K


@benchmark
def subexpr_rec(A, B, K):
    K = A @ B
    K = K + K
    return K


def exp09_common_subexpressions(b, n):
    A = tf.random.normal([n, n], dtype=tf.float64)
    B = tf.random.normal([n, n], dtype=tf.float64)
    K = tf.zeros((n, n), dtype=tf.float64)

    res1 = b.benchmark('subexpr_nai', subexpr_nai, A, B, K)
    res2 = b.benchmark('subexpr_rec', subexpr_rec, A, B, K)
    logger.info('CommonSubExpr correctness: {}'.format(tf.debugging.assert_near(res1, res2, rtol=1e-05, atol=1e-08)))
