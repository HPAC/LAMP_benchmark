from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('PropertiesSolve')


def solve(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(B)
    cache_scrub()
    start = time.perf_counter()
    ct = np.linalg.solve(at, bt)
    end = time.perf_counter()
    return end-start, ct


def properties_solve(b, m, rhs):

    B = np.random.randn(m, rhs)

    # SPD
    A = np.random.randn(m, m)
    A = A + A.T + np.eye(m, dtype=np.float64) * m
    logger.info('A is symmetric: {}'.format(np.allclose(A, A.T)))
    try:
        np.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except np.linalg.LinAlgError:
        logger.info('A is SPD: False')
    b.benchmark('solve_spd', solve, A, B)

    # Symmetric
    A = np.random.randn(m, m)
    A = A + A.T
    A[1, 1] = -1.0
    logger.info('A is symmetric: {}'.format(np.allclose(A, A.T)))
    try:
        np.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except np.linalg.LinAlgError:
        logger.info('A is SPD: False')
    b.benchmark('solve_sym', solve, A, B)

    # Triangular
    A = np.random.randn(m, m)
    A = np.tril(A)
    logger.info('A is triangular: {}'.format(np.allclose(A, np.tril(A))))
    b.benchmark('solve_tri', solve, A, B)

    # Diagonal
    A = np.random.randn(m, m)
    A = np.diag(np.diag(A))
    logger.info('A is diagonal: {}'.format(np.allclose(A, np.diag(np.diag(A)))))
    b.benchmark('solve_dia', solve, A, B)
