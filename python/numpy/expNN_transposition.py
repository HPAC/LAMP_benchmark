from scipy import linalg
import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('expNN_transposition')

@benchmark
def tr_tt_implicit(A, B, C):
    C = A.T @ B.T
    return C

@benchmark
def tr_tt_explicit(A, B, C):
    linalg.blas.dgemm(1.0, A, B, 0.0, C, trans_a=True, trans_b=True, overwrite_c=True)
    return C

@benchmark
def tr_nt_implicit(A, B, C):
    C = A @ B.T
    return C

@benchmark
def tr_nt_explicit(A, B, C):
    linalg.blas.dgemm(1.0, A, B, 0.0, C, trans_a=False, trans_b=True, overwrite_c=True)
    return C

@benchmark
def tr_tn_implicit(A, B, C):
    C = A.T @ B
    return C

@benchmark
def tr_tn_explicit(A, B, C):
    linalg.blas.dgemm(1.0, A, B, 0.0, C, trans_a=True, trans_b=False, overwrite_c=True)
    return C

@benchmark
def tr_nn_implicit(A, B, C):
    C = A @ B
    return C

@benchmark
def tr_nn_explicit(A, B, C):
    linalg.blas.dgemm(1.0, A, B, 0.0, C, trans_a=False, trans_b=False, overwrite_c=True)
    return C


def expNN_transposition(b, n):

    tn = int(n / 10)
    A = np.random.randn(tn, tn)
    B = np.random.randn(tn, tn)
    C = np.random.randn(tn, tn)

    res1 = b.benchmark('tr_nn_implicit', tr_nn_implicit, A, B, C)
    res3 = b.benchmark('tr_tn_implicit', tr_tn_implicit, A, B, C)
    res5 = b.benchmark('tr_nt_implicit', tr_nt_implicit, A, B, C)
    res7 = b.benchmark('tr_tt_implicit', tr_tt_implicit, A, B, C)

    C = C.ravel(order='F').reshape(C.shape, order='F')
    res2 = b.benchmark('tr_nn_explicit', tr_nn_explicit, A, B, C)
    res4 = b.benchmark('tr_tn_explicit', tr_tn_explicit, A, B, C)
    res6 = b.benchmark('tr_nt_explicit', tr_nt_explicit, A, B, C)
    res8 = b.benchmark('tr_tt_explicit', tr_tt_explicit, A, B, C)

    logger.info('tr_nn correctness: {}'.format(np.allclose(res1, res2)))
    logger.info('tr_tn correctness: {}'.format(np.allclose(res3, res4)))
    logger.info('tr_nt correctness: {}'.format(np.allclose(res5, res6)))
    logger.info('tr_tt correctness: {}'.format(np.allclose(res7, res8)))
