import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp03_syr2k')


@benchmark
def syr2k_implicit_noup(A, B, C):
    C = A @ B.T + B @ A.T
    return C


def exp03_syr2k(b, n):
    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)
    C = C + C.T

    res = b.benchmark('syr2k_implicit_noup', syr2k_implicit_noup, A, B, C)
