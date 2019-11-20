from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('Syrk')


def syrk_implicit(A, C):

    at = copy.deepcopy(A)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ at.T + ct
    end = time.perf_counter()

    return end-start, ct


def syrk_implicit_compact(A, C):

    at = copy.deepcopy(A)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct += at @ at.T
    end = time.perf_counter()

    return end-start, ct


def syrk_implicit_noup(A, C):

    at = copy.deepcopy(A)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ at.T
    end = time.perf_counter()

    return end-start, ct


def syrk_explicit(A, C):

    at = copy.deepcopy(A)
    ct = copy.deepcopy(C)
    ct = ct.ravel(order='F').reshape(ct.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dsyrk(1.0, at, 1.0, ct, overwrite_c=True, lower=True, trans=False)
    end = time.perf_counter()
    return end-start, ct


def kernel_invocations_syrk(b, *args):

    res1 = b.benchmark('syrk_implicit', syrk_implicit, *args)
    res2 = b.benchmark('syrk_implicit_compact', syrk_implicit_compact, *args)
    res3 = b.benchmark('syrk_explicit', syrk_explicit, *args)
    res4 = b.benchmark('syrk_implicit_noup', syrk_implicit_noup, *args)
    logger.info('Syrk correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res2, k=0))))
    logger.info('Syrk correctness: {}'.format(np.allclose(np.tril(res1, k=0), np.tril(res3, k=0))))
