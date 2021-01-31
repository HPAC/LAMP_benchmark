import logging
import numpy as np
from scipy import linalg
from benchmarker import benchmark

logger = logging.getLogger('exp04_update_of_c')

@benchmark
def add(A, B):
    B = A + B
    return B

@benchmark
def scal(A):
    A = 3.0 * A
    return A


@benchmark
def gemm_implicit(A, B, C):
    C = A @ B + C
    return C

@benchmark
def gemm_implicit_compact(A, B, C):
    C += A @ B
    return C

@benchmark
def gemm_implicit_coeff(A, B, C):
    C = 3.0 * A @ B + C
    return C

@benchmark
def gemm_implicit_double_coeff(A, B, C):
    C = 3.0 * A @ B + 3.0 * C
    return C

@benchmark
def gemm_explicit(A, B, C):
    linalg.blas.dgemm(1.0, A, B, 1.0, C, trans_a=False, trans_b=False, overwrite_c=True)
    return C


def exp04_update_of_c(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)

    b.benchmark('add', add, A, B)
    b.benchmark('scal', scal, A)

    res1 = b.benchmark('gemm_implicit', gemm_implicit, A, B, C)
    res2 = b.benchmark('gemm_implicit_compact', gemm_implicit_compact, A, B, C)
    res3 = b.benchmark('gemm_explicit', gemm_explicit, A, B, C)

    res4 = b.benchmark('gemm_implicit_coeff', gemm_implicit_coeff, A, B, C)
    res5 = b.benchmark('gemm_implicit_double_coeff', gemm_implicit_double_coeff, A, B, C)

    logger.info('Gemm correctness: {}'.format(np.allclose(res1, res2)))
    logger.info('Gemm correctness: {}'.format(np.allclose(res1, res3)))