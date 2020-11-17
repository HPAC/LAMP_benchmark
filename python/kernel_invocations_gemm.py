from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('Gemm')


def gemm_implicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt + ct
    end = time.perf_counter()

    return end-start, ct


def gemm_implicit_compact(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct += at @ bt
    end = time.perf_counter()

    return end-start, ct


def gemm_implicit_coeff(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = 3.0 * at @ bt + ct
    end = time.perf_counter()

    return end-start, ct


def gemm_implicit_double_coeff(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = 3.0 * at @ bt + 3.0 * ct
    end = time.perf_counter()

    return end-start, ct


def gemm_implicit_noup(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt
    end = time.perf_counter()

    return end-start, ct


def gemm_explicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    ct = ct.ravel(order='F').reshape(ct.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dgemm(1.0, at, bt, 1.0, ct, trans_a=False, trans_b=False, overwrite_c=True)
    end = time.perf_counter()
    return end-start, ct


def trmm_implicit(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    cache_scrub()
    start = time.perf_counter()
    bt = at @ bt
    end = time.perf_counter()
    return end-start, bt


def trmm_explicit(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    bt = bt.ravel(order='F').reshape(bt.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dtrmm(1.0, at, bt, diag=False, trans_a=False, side=False,
                      lower=True, overwrite_b=True)  # diag specifies unit triangular
    end = time.perf_counter()
    return end-start, bt


def diagmm(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt
    end = time.perf_counter()

    return end-start, ct


def kernel_invocations_gemm(b, *args):

    res1 = b.benchmark('gemm_implicit', gemm_implicit, *args)
    res2 = b.benchmark('gemm_implicit_compact', gemm_implicit_compact, *args)
    res3 = b.benchmark('gemm_explicit', gemm_explicit, *args)

    res4 = b.benchmark('gemm_implicit_noup', gemm_implicit_noup, *args)

    res4 = b.benchmark('gemm_implicit_coeff', gemm_implicit_coeff, *args)
    res4 = b.benchmark('gemm_implicit_double_coeff', gemm_implicit_double_coeff, *args)

    Asq = np.random.randn(args[0].shape[0], args[0].shape[0])
    Bsq = np.random.randn(args[0].shape[0], args[0].shape[0])
    Csq = np.random.randn(args[0].shape[0], args[0].shape[0])

    Asq = np.tril(Asq)
    logger.debug('Asq is triangualar'.format(np.allclose(Asq, np.tril(Asq))))
    res7 = b.benchmark('trmm_implicit', trmm_implicit, Asq, Bsq)
    res8 = b.benchmark('trmm_explicit', trmm_explicit, Asq, Bsq)

    Ad = np.diag(np.diag(Asq))
    res9 = b.benchmark('diagmm', diagmm, Ad, Bsq, Csq)

    logger.info('Gemm correctness: {}'.format(np.allclose(res1, res2)))
    logger.info('Gemm correctness: {}'.format(np.allclose(res1, res3)))
    logger.info('Trmm correctness: {}'.format(np.allclose(res7, res8)))
