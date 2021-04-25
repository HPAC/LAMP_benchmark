import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp11_blocked_matrices')


@benchmark
def blocked_solve_naive(A1, A2, B, C):
    C = np.linalg.solve(np.concatenate(
        (np.concatenate((A1, np.zeros((A1.shape[0], A1.shape[1]), dtype=np.float64)), axis=1),
         np.concatenate((np.zeros((A2.shape[0], A2.shape[1]), dtype=np.float64), A2), axis=1)), axis=0), B)
    return C


@benchmark
def blocked_solve_recommended(A1, A2, B, C):
    b1 = B[0:A1.shape[0], 0:B.shape[1]]
    b2 = B[A1.shape[0]:, 0:B.shape[1]]
    C = np.concatenate((np.linalg.solve(A1, b1), np.linalg.solve(A2, b2)), axis=0)
    return C


def exp11_blocked_matrices(b, n):
    bm_n = int(n / 2)
    A1 = np.random.randn(bm_n, bm_n)
    A2 = np.random.randn(bm_n, bm_n)
    B = np.random.randn(2 * bm_n, 2 * bm_n)
    C = np.zeros((2 * bm_n, 2 * bm_n), dtype=np.float64)

    res1 = b.benchmark("compact", blocked_solve_naive, A1, A2, B, C)
    res2 = b.benchmark("blocked", blocked_solve_recommended, A1, A2, B, C)
    logger.info('PartitionedMatrices correctness: {}'.format(np.allclose(res1, res2)))
