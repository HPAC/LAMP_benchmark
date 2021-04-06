import logging
from benchmarker import benchmark
import numpy as np
import tensorflow as tf

logger = logging.getLogger('exp08_properties_in_linear_systems')

@benchmark
def solve(A, B, C):
    C = tf.linalg.solve(A, B)
    return C


def exp08_properties_in_linear_systems(b, n, rhs):

    B = tf.random.normal([n, rhs], dtype=tf.float64)
    C = tf.zeros((n, rhs), dtype=tf.float64)

    # SPD
    A = tf.random.normal([n, n], dtype=tf.float64)
    A = A + tf.transpose(A) + tf.eye(n, dtype=tf.float64) * n
    logger.info('A is symmetric: {}'.format(tf.debugging.assert_near(A, tf.transpose(A), rtol=1e-05, atol=1e-08)))
    try:
        tf.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except np.linalg.LinAlgError:
        logger.info('A is SPD: False')
    b.benchmark('solve_spd', solve, A, B, C)

    # Symmetric
    A = tf.random.normal([n, n], dtype=tf.float64)
    A = A + tf.transpose(A)
    A = tf.tensor_scatter_nd_update(A, [[1, 1]], [-1.0])
    logger.info('A is symmetric: {}'.format(tf.debugging.assert_near(A, tf.transpose(A), rtol=1e-05, atol=1e-08)))
    """
    try:
        tf.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except np.linalg.LinAlgError:
        logger.info('A is SPD: False')
    """
    b.benchmark('solve_sym', solve, A, B, C)

    # Triangular
    A = tf.random.normal([n, n], dtype=tf.float64)
    A = tf.linalg.band_part(A, -1, 0)
    logger.info('A is triangular: {}'.format(tf.debugging.assert_near(A, tf.linalg.band_part(A, -1, 0), rtol=1e-05, atol=1e-08)))
    b.benchmark('solve_tri', solve, A, B, C)

    # Diagonal
    A = tf.random.normal([n, n], dtype=tf.float64)
    A = tf.linalg.diag(tf.linalg.diag_part(A))
    logger.info('A is diagonal: {}'.format(tf.debugging.assert_near(A, tf.linalg.diag(tf.linalg.diag_part(A)), rtol=1e-05, atol=1e-08)))
    b.benchmark('solve_dia', solve, A, B, C)
