import logging
from benchmarker import benchmark
import torch as torch

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

    licm_n = int(n / 10)
    A = torch.randn(licm_n, licm_n)
    B = torch.randn(licm_n, licm_n)
    C = torch.randn(licm_n)
    temp = torch.zeros((licm_n, licm_n), dtype=torch.float64)

    res1 = b.benchmark("loop_nai", naive_loop, A, B, C, temp)
    res2 = b.benchmark("loop_rec", recommended_loop, A, B, C, temp)
    logger.info('LICM correctness: {}'.format(torch.allclose(res1, res2)))
