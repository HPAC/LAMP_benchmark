import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp05_explicit_inversion')


@benchmark
def solve_nai(A, B):
    C = np.linalg.inv(A) @ B
    return C


@benchmark
def solve_rec(A, B):
    C = np.linalg.solve(A, B)
    return C


def exp05_explicit_inversion(b, n):
    A = np.random.randn(n, n)
    B = np.random.randn(n, 200)

    res1 = b.benchmark('solve_nai', solve_nai, A, B)
    res2 = b.benchmark('solve_rec', solve_rec, A, B)
    logger.info('Solve correctness: {}'.format(np.allclose(res1, res2)))

    B = np.random.randn(n, 5 * n)  # B.rows , 5 * A.rows
    res3 = b.benchmark('solve_large_nai', solve_nai, A, B)
    res4 = b.benchmark('solve_large_rec', solve_rec, A, B)
    logger.info('Solve correctness: {}'.format(np.allclose(res3, res4)))
