import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp06_optimal_parenthesization')

@benchmark
def mc_l_r_orig(A, B, C, res):
    res = C @ A @ B
    return res

@benchmark
def mc_l_r_guid(A, B, C, res):
    res = (C @ A) @ B
    return res

@benchmark
def mc_r_l_orig(A, B, C, res):
    res = A @ B @ C
    return res

@benchmark
def mc_r_l_guid(A, B, C, res):
    res = A @ (B @ C)
    return res

@benchmark
def mc_mixed_orig(A, B, C, D, res):
    res = A @ B @ C @ D
    return res

@benchmark
def mc_mixed_guid(A, B, C, D, res):
    res = (A @ B) @ (C @ D)
    return res


def exp06_optimal_parenthesization(b, n):

    n_5 = int(n/5)
    A = tf.random.normal([n, n], dtype=tf.float64)
    B = tf.random.normal([n, n], dtype=tf.float64)

    C = tf.random.normal([n_5, n], dtype=tf.float64)
    res = tf.zeros((C.shape[0], B.shape[1]), dtype=tf.float64)
    res1 = b.benchmark('mc_l_r_orig', mc_l_r_orig, A, B, C, res)
    res2 = b.benchmark('mc_l_r_guid', mc_l_r_guid, A, B, C, res)
    logger.info('mc_l_r correctness: {}'.format(tf.debugging.assert_near(res1, res2, rtol=1e-05, atol=1e-08)))

    C = tf.random.normal([n, n_5], dtype=tf.float64)
    res = tf.zeros((A.shape[0], C.shape[1]), dtype=tf.float64)
    res3 = b.benchmark('mc_r_l_orig', mc_r_l_orig, A, B, C, res)
    res4 = b.benchmark('mc_r_l_guid', mc_r_l_guid, A, B, C, res)
    logger.info('mc_r_l correctness: {}'.format(tf.debugging.assert_near(res3, res4, rtol=1e-05, atol=1e-08)))

    A = tf.random.normal([n, n], dtype=tf.float64)
    B = tf.random.normal([n, n_5], dtype=tf.float64)
    C = tf.random.normal([n_5, n], dtype=tf.float64)
    D = tf.random.normal([n, n], dtype=tf.float64)
    res = tf.zeros((A.shape[0], D.shape[1]), dtype=tf.float64)
    res5 = b.benchmark('mc_mixed_orig', mc_mixed_orig, A, B, C, D, res)
    res6 = b.benchmark('mc_mixed_guid', mc_mixed_guid, A, B, C, D, res)
    logger.info('mc_mixed correctness: {}'.format(tf.debugging.assert_near(res5, res6, rtol=1e-05, atol=1e-08)))
