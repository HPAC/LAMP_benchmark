import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp08_properties_in_linear_systems')


@benchmark
def solve(A, B, C):
    C = np.linalg.solve(A, B)
    return C


def exp08_properties_in_linear_systems(b, n, rhs):
    B = np.random.randn(n, rhs)
    C = np.zeros((n, rhs), dtype=np.float64)

    # SPD
    A = np.random.randn(n, n)
    A = A + A.T + np.eye(n, dtype=np.float64) * n
    logger.info('A is symmetric: {}'.format(np.allclose(A, A.T)))
    try:
        np.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except np.linalg.LinAlgError:
        logger.info('A is SPD: False')
    b.benchmark('solve_spd', solve, A, B, C)

    # Symmetric
    A = np.random.randn(n, n)
    A = A + A.T
    A[1, 1] = -1.0
    logger.info('A is symmetric: {}'.format(np.allclose(A, A.T)))
    try:
        np.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except np.linalg.LinAlgError:
        logger.info('A is SPD: False')
    b.benchmark('solve_sym', solve, A, B, C)

    # Triangular
    A = np.random.randn(n, n)
    A = np.tril(A)
    logger.info('A is triangular: {}'.format(np.allclose(A, np.tril(A))))
    b.benchmark('solve_tri', solve, A, B, C)

    # Diagonal
    A = np.random.randn(n, n)
    A = np.diag(np.diag(A))
    logger.info('A is diagonal: {}'.format(np.allclose(A, np.diag(np.diag(A)))))
    b.benchmark('solve_dia', solve, A, B, C)
