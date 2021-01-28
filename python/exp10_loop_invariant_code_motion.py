import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp10_loop_invariant_code_motion')

@benchmark
def naive_loop(A, B, C, temp):
    for i in range(C.shape[0]):
        temp = A @ B
        C[i] = temp[i, i]
    return C

@benchmark
def recommended_loop(A, B, C, temp):
    temp = A @ B
    for i in range(C.shape[0]):
        C[i] = temp[i, i]
    return C


def exp10_loop_invariant_code_motion(b, n):

    ipn = int(n / 10)
    A = np.random.randn(ipn, ipn)
    B = np.random.randn(ipn, ipn)
    C = np.random.randn(ipn)
    temp = np.zeros((A.shape[0], B.shape[1]), dtype=np.float64)

    res1 = b.benchmark("loop_nai", naive_loop, A, B, C, temp)
    res2 = b.benchmark("loop_rec", recommended_loop, A, B, C, temp)
    logger.info('IndexProblems correctness: {}'.format(np.allclose(res1, res2)))