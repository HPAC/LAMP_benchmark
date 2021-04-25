from benchmarker import benchmark
import logging
import numpy as np
from scipy import linalg

logger = logging.getLogger('exp07_properties_multiplication')

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


def exp07_properties_multiplication(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)
    B_fortran_style = B.ravel(order='F').reshape(B.shape, order='F')

    A = np.tril(A)
    logger.debug('A is triangualar'.format(np.allclose(A, np.tril(A))))
    res1 = b.benchmark('trmm_implicit', trmm_implicit, A, B)
    res2 = b.benchmark('trmm_explicit', trmm_explicit, A, B_fortran_style)

    Ad = np.diag(np.diag(A))
    res3 = b.benchmark('diagmm', diagmm, Ad, B, C)

    logger.info('Trmm correctness: {}'.format(np.allclose(res1, res2)))
