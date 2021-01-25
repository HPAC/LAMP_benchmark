from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub
from benchmarker import benchmark

logger = logging.getLogger('Syrk')

@benchmark
def syrk_implicit(A, C):
    C = A @ A.T + C
    return C

@benchmark
def syrk_implicit_compact(A, C):
    C += A @ A.T
    return C

@benchmark
def syrk_implicit_noup(A, C):
    C = A @ A.T
    return C

@benchmark
def syrk_explicit(A, C):
    linalg.blas.dsyrk(1.0, A, 1.0, C, overwrite_c=True, lower=True, trans=False)
    return C


def exp02_syrk(b, n):

    A = np.random.randn(n, n)
    C = np.random.randn(n, n)
    C = C + C.T

    res1 = b.benchmark('syrk_implicit', syrk_implicit, A, C)
    res2 = b.benchmark('syrk_implicit_compact', syrk_implicit_compact, A, C)
    res4 = b.benchmark('syrk_implicit_noup', syrk_implicit_noup, A, C)
    C = C.ravel(order='F').reshape(C.shape, order='F')
    res3 = b.benchmark('syrk_explicit', syrk_explicit, A, C)

    logger.info('Syrk correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res2, k=0))))
    logger.info('Syrk correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res3, k=0))))
