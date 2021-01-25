from benchmarker import benchmark
import logging
import numpy as np
from scipy import linalg

### logger = logging.getLogger('Gemm')

@benchmark
def trmm_implicit(A, B):
    B = A @ B
    return B


@benchmark
def trmm_explicit(A, B):
    linalg.blas.dtrmm(1.0, A, B, diag=False, trans_a=False, side=False,
                      lower=True, overwrite_b=True)  # diag specifies unit triangular
    return B


def exp07_properties_multiplication(b, n):

    Asq = np.random.randn(n, n)
    Bsq = np.random.randn(n, n)

    Asq = np.tril(Asq)
    logger.debug('Asq is triangualar'.format(np.allclose(Asq, np.tril(Asq))))
    res7 = b.benchmark('trmm_implicit', trmm_implicit, Asq, Bsq)
    res8 = b.benchmark('trmm_explicit', trmm_explicit, Asq, Bsq)

    logger.info('Trmm correctness: {}'.format(np.allclose(res7, res8)))