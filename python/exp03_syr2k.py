from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub
from benchmarker import benchmark

logger = logging.getLogger('Syr2k')

@benchmark
def syr2k_implicit(A, B, C):
    C = A @ B.T + B @ A.T + C
    return C

@benchmark
def syr2k_implicit_noup(A, B, C):
    C = A @ B.T + B @ A.T
    return C

@benchmark
def syr2k_implicit_compact(A, B, C):
    C += A @ B.T + B @ A.T
    return C

@benchmark
def syr2k_explicit(A, B, C):
    linalg.blas.dsyr2k(1.0, A, B, 1.0, C, overwrite_c=True, lower=True, trans=False)
    return C


def exp03_syr2k(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)
    C = C + C.T

    res1 = b.benchmark('syr2k_implicit', syr2k_implicit, A, B, C)
    res3 = b.benchmark('syr2k_implicit_compact', syr2k_implicit_compact, A, B, C)
    res4 = b.benchmark('syr2k_implicit_noup', syr2k_implicit_noup, A, B, C)
    C = C.ravel(order='F').reshape(C.shape, order='F')
    res2 = b.benchmark('syr2k_explicit', syr2k_explicit, A, B, C)
    logger.info('Syr2k correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res2, k=0))))
    logger.info('Syr2k correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res3, k=0))))
