from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('DiagonalElements')

def diagonal_mult_nai(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(B)
    ct = ct.diagonal()
    cache_scrub()
    start = time.perf_counter()
    ct = np.diagonal(at @ bt)
    end = time.perf_counter()

    return end-start, ct

def diagonal_nai(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(B)
    ct = ct.diagonal()
    cache_scrub()
    start = time.perf_counter()
    ct = np.diagonal(at + bt)
    end = time.perf_counter()

    return end-start, ct


def diagonal_rec(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(B)
    ct = ct.diagonal()
    cache_scrub()
    start = time.perf_counter()
    ct = np.diagonal(at) + np.diagonal(bt)
    end = time.perf_counter()

    return end-start, ct


def diagonal_elements(b, *args):

    res3 = b.benchmark('diag_mult_nai', diagonal_mult_nai, *args)
    res1 = b.benchmark('diag_add_nai', diagonal_nai, *args)
    res2 = b.benchmark('diag_add_rec', diagonal_rec, *args)
    logger.info('DiagonalElements correctness: {}'.format(np.allclose(res1, res2)))
