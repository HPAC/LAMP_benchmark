import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp10_loop_invariant_code_motion')


@benchmark
def naive_loop(A, B, c, temp):
    for i in range(c.shape[0]):
        temp = A @ B
        c[i] = temp[i, i]
    return c


@benchmark
def recommended_loop(A, B, c, temp):
    temp = A @ B
    for i in range(c.shape[0]):
        c[i] = temp[i, i]
    return c


def exp10_loop_invariant_code_motion(b, n):
    licm_n = int(n / 10)
    A = np.random.randn(licm_n, licm_n)
    B = np.random.randn(licm_n, licm_n)
    c = np.random.randn(licm_n)
    temp = np.zeros((licm_n, licm_n), dtype=np.float64)

    res1 = b.benchmark("loop_nai", naive_loop, A, B, c, temp)
    res2 = b.benchmark("loop_rec", recommended_loop, A, B, c, temp)
    logger.info('IndexProblems correctness: {}'.format(np.allclose(res1, res2)))
