from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('MatrixChain')


def mc_l_r_orig(m, A, B):

    at = copy.deepcopy(A)
    mt = copy.deepcopy(m)
    bt = copy.deepcopy(B)
    ct = np.zeros((m.shape[0], B.shape[1]), dtype=np.float64)
    cache_scrub()
    start = time.perf_counter()
    ct = mt @ at @ bt
    end = time.perf_counter()

    return end-start, ct


def mc_l_r_guid(m, A, B):

    at = copy.deepcopy(A)
    mt = copy.deepcopy(m)
    bt = copy.deepcopy(B)
    ct = np.zeros((m.shape[0], B.shape[1]), dtype=np.float64)
    cache_scrub()
    start = time.perf_counter()
    ct = (mt @ at) @ bt
    end = time.perf_counter()

    return end-start, ct


def mc_r_l_orig(m, A, B):

    at = copy.deepcopy(A)
    mt = copy.deepcopy(m)
    bt = copy.deepcopy(B)
    ct = np.zeros((A.shape[0], m.shape[1]), dtype=np.float64)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt @ mt
    end = time.perf_counter()

    return end-start, ct


def mc_r_l_guid(m, A, B):

    at = copy.deepcopy(A)
    mt = copy.deepcopy(m)
    bt = copy.deepcopy(B)
    ct = np.zeros((A.shape[0], m.shape[1]), dtype=np.float64)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ (bt @ mt)
    end = time.perf_counter()

    return end-start, ct


def mc_mixed_orig(A, B, C, D):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    dt = copy.deepcopy(D)
    res = np.zeros((A.shape[0], D.shape[1]), dtype=np.float64)
    cache_scrub()
    start = time.perf_counter()
    res = at @ bt @ ct @ dt
    end = time.perf_counter()

    return end-start, res


def mc_mixed_guid(A, B, C, D):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    dt = copy.deepcopy(D)
    res = np.zeros((A.shape[0], D.shape[1]), dtype=np.float64)
    cache_scrub()
    start = time.perf_counter()
    res = (at @ bt) @ (ct @ dt)
    end = time.perf_counter()

    return end-start, res


def matrix_chain(b, *args):

    m = args[0].shape[0]  # nrows A
    k = args[0].shape[1]  # ncols A
    n = args[1].shape[1]  # ncols B
    k_half = int(k/2)

    C = np.random.randn(k_half, m)
    res1 = b.benchmark('mc_l_r_orig', mc_l_r_orig, C, *args)
    res2 = b.benchmark('mc_l_r_guid', mc_l_r_guid, C, *args)
    logger.info('mc_l_r correctness: {}'.format(np.allclose(res1, res2)))

    C = np.random.randn(n, k_half)
    res1 = b.benchmark('mc_r_l_orig', mc_r_l_orig, C, *args)
    res2 = b.benchmark('mc_r_l_guid', mc_r_l_guid, C, *args)
    logger.info('mc_r_l correctness: {}'.format(np.allclose(res1, res2)))

    A = np.random.randn(m, k)
    B = np.random.randn(k, k_half)
    C = np.random.randn(k_half, k)
    D = np.random.randn(k, n)
    res1 = b.benchmark('mc_mixed_orig', mc_mixed_orig, A, B, C, D)
    res2 = b.benchmark('mc_mixed_guid', mc_mixed_guid, A, B, C, D)
    logger.info('mc_mixed correctness: {}'.format(np.allclose(res1, res2)))
