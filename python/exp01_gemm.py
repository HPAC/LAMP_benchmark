from benchmarker import benchmark
import logging
import numpy as np

logger = logging.getLogger('exp01_gemm')

@benchmark
def gemm_implicit_noup(A, B, C):
    C = A @ B
    return C


def exp01_gemm(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)

    res = b.benchmark('gemm_implicit_noup', gemm_implicit_noup, A, B, C)





