import logging
from benchmarker import benchmark
import torch as torch

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
    A = torch.randn((licm_n, licm_n), dtype=torch.float64)
    B = torch.randn((licm_n, licm_n), dtype=torch.float64)
    c = torch.randn(licm_n, dtype=torch.float64)
    temp = torch.zeros((licm_n, licm_n), dtype=torch.float64)

    res1 = b.benchmark("loop_nai", naive_loop, A, B, c, temp)
    res2 = b.benchmark("loop_rec", recommended_loop, A, B, c, temp)
    logger.info('LICM correctness: {}'.format(torch.allclose(res1, res2)))
