from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('Transposition')


def tr_tt_implicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at.T @ bt.T
    end = time.perf_counter()

    return end-start, ct


def tr_tt_explicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    ct = ct.ravel(order='F').reshape(ct.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dgemm(1.0, at, bt, 0.0, ct, trans_a=True, trans_b=True, overwrite_c=True)
    end = time.perf_counter()
    return end-start, ct


def tr_nt_implicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt.T
    end = time.perf_counter()

    return end-start, ct


def tr_nt_explicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    ct = ct.ravel(order='F').reshape(ct.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dgemm(1.0, at, bt, 0.0, ct, trans_a=False, trans_b=True, overwrite_c=True)
    end = time.perf_counter()
    return end-start, ct


def tr_tn_implicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at.T @ bt
    end = time.perf_counter()

    return end-start, ct


def tr_tn_explicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    ct = ct.ravel(order='F').reshape(ct.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dgemm(1.0, at, bt, 0.0, ct, trans_a=True, trans_b=False, overwrite_c=True)
    end = time.perf_counter()
    return end-start, ct


def tr_nn_implicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt
    end = time.perf_counter()

    return end-start, ct


def tr_nn_explicit(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    ct = ct.ravel(order='F').reshape(ct.shape, order='F')
    cache_scrub()
    start = time.perf_counter()
    linalg.blas.dgemm(1.0, at, bt, 0.0, ct, trans_a=False, trans_b=False, overwrite_c=True)
    end = time.perf_counter()
    return end-start, ct


def transposition(b, *args):

    res1 = b.benchmark('tr_nn_implicit', tr_nn_implicit, *args)
    res2 = b.benchmark('tr_nn_explicit', tr_nn_explicit, *args)
    logger.info('tr_nn correctness: {}'.format(np.allclose(res1, res2)))

    res1 = b.benchmark('tr_tn_implicit', tr_tn_implicit, *args)
    res2 = b.benchmark('tr_tn_explicit', tr_tn_explicit, *args)
    logger.info('tr_tn correctness: {}'.format(np.allclose(res1, res2)))

    res1 = b.benchmark('tr_nt_implicit', tr_nt_implicit, *args)
    res2 = b.benchmark('tr_nt_explicit', tr_nt_explicit, *args)
    logger.info('tr_nt correctness: {}'.format(np.allclose(res1, res2)))

    res1 = b.benchmark('tr_tt_implicit', tr_tt_implicit, *args)
    res2 = b.benchmark('tr_tt_explicit', tr_tt_explicit, *args)
    logger.info('tr_tt correctness: {}'.format(np.allclose(res1, res2)))
