from benchmarker import benchmark
import logging
import numpy as np
from scipy import linalg

logger = logging.getLogger('exp01_gemm')

@benchmark
def gemm_implicit_noup(A, B, C):
    C = A @ B
    return C

@benchmark
def diagmm(A, B, C):
    C = A @ B
    return C


def exp01_gemm(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)

    res1 = b.benchmark('gemm_implicit_noup', gemm_implicit_noup, A, B, C)

    Asq = np.random.randn(A.shape[0], A.shape[0])
    Bsq = np.random.randn(A.shape[0], A.shape[0])
    Csq = np.random.randn(A.shape[0], A.shape[0])

    Asq = np.tril(Asq)
    logger.debug('Asq is triangualar'.format(np.allclose(Asq, np.tril(Asq))))

    Ad = np.diag(np.diag(Asq))
    res2 = b.benchmark('diagmm', diagmm, Ad, Bsq, Csq)



