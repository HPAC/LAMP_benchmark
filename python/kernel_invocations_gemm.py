from benchmarker import benchmark
import logging
import numpy as np
from scipy import linalg

logger = logging.getLogger('Gemm')


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
def gemm_implicit_noup(A, B, C):
    C = A @ B
    return C


@benchmark
def gemm_explicit(A, B, C):
    linalg.blas.dgemm(1.0, A, B, 1.0, C, trans_a=False, trans_b=False, overwrite_c=True)
    return C


@benchmark
def trmm_implicit(A, B):
    B = A @ B
    return B


@benchmark
def trmm_explicit(A, B):
    linalg.blas.dtrmm(1.0, A, B, diag=False, trans_a=False, side=False,
                      lower=True, overwrite_b=True)  # diag specifies unit triangular
    return B


@benchmark
def diagmm(A, B, C):
    C = A @ B
    return C


def exp01_gemm(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)

    res1 = b.benchmark('gemm_implicit', gemm_implicit, A, B, C)
    res2 = b.benchmark('gemm_implicit_compact', gemm_implicit_compact, A, B, C)
    res3 = b.benchmark('gemm_explicit', gemm_explicit, A, B, C)

    res4 = b.benchmark('gemm_implicit_noup', gemm_implicit_noup, A, B, C)

    res4 = b.benchmark('gemm_implicit_coeff', gemm_implicit_coeff, A, B, C)
    res4 = b.benchmark('gemm_implicit_double_coeff', gemm_implicit_double_coeff, A, B, C)

    Asq = np.random.randn(A.shape[0], A.shape[0])
    Bsq = np.random.randn(A.shape[0], A.shape[0])
    Csq = np.random.randn(A.shape[0], A.shape[0])

    Asq = np.tril(Asq)
    logger.debug('Asq is triangualar'.format(np.allclose(Asq, np.tril(Asq))))
    res7 = b.benchmark('trmm_implicit', trmm_implicit, Asq, Bsq)
    res8 = b.benchmark('trmm_explicit', trmm_explicit, Asq, Bsq)

    Ad = np.diag(np.diag(Asq))
    res9 = b.benchmark('diagmm', diagmm, Ad, Bsq, Csq)

    logger.info('Gemm correctness: {}'.format(np.allclose(res1, res2)))
    logger.info('Gemm correctness: {}'.format(np.allclose(res1, res3)))
    logger.info('Trmm correctness: {}'.format(np.allclose(res7, res8)))
