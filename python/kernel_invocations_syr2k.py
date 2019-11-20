from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('Syr2k')


def syr2k_implicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt.T + bt @ at.T + ct
    end = time.perf_counter()

    return end-start, ct


def syr2k_implicit_noup(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt.T + bt @ at.T
    end = time.perf_counter()

    return end-start, ct


def syr2k_implicit_compact(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct += at @ bt.T + bt @ at.T
    end = time.perf_counter()

    return end-start, ct


def syr2k_explicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    ct = ct.ravel(order='F').reshape(ct.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dsyr2k(1.0, at, bt, 1.0, ct, overwrite_c=True, lower=True, trans=False)
    end = time.perf_counter()
    return end-start, ct


def kernel_invocations_syr2k(b, *args):

    res1 = b.benchmark('syr2k_implicit', syr2k_implicit, *args)
    res2 = b.benchmark('syr2k_explicit', syr2k_explicit, *args)
    res3 = b.benchmark('syr2k_implicit_compact', syr2k_implicit_compact, *args)
    res4 = b.benchmark('syr2k_implicit_noup', syr2k_implicit_noup, *args)
    logger.info('Syr2k correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res2, k=0))))
    logger.info('Syr2k correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res3, k=0))))
