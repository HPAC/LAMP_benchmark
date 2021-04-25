import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp06_optimal_parenthesization')


@benchmark
def mc_l_r_orig(A, B, C, res):
    res = C @ A @ B
    return res


@benchmark
def mc_l_r_guid(A, B, C, res):
    res = (C @ A) @ B
    return res


@benchmark
def mc_r_l_orig(A, B, C, res):
    res = A @ B @ C
    return res


@benchmark
def mc_r_l_guid(A, B, C, res):
    res = A @ (B @ C)
    return res


@benchmark
def mc_mixed_orig(A, B, C, D, res):
    res = A @ B @ C @ D
    return res


@benchmark
def mc_mixed_guid(A, B, C, D, res):
    res = (A @ B) @ (C @ D)
    return res


def exp06_optimal_parenthesization(b, n):
    n_5 = int(n / 5)
    A = np.random.randn(n, n)
    B = np.random.randn(n, n)

    C = np.random.randn(n_5, n)
    res = np.zeros((C.shape[0], B.shape[1]), dtype=np.float64)
    res1 = b.benchmark('mc_l_r_orig', mc_l_r_orig, A, B, C, res)
    res2 = b.benchmark('mc_l_r_guid', mc_l_r_guid, A, B, C, res)
    logger.info('mc_l_r correctness: {}'.format(np.allclose(res1, res2)))

    C = np.random.randn(n, n_5)
    res = np.zeros((A.shape[0], C.shape[1]), dtype=np.float64)
    res3 = b.benchmark('mc_r_l_orig', mc_r_l_orig, A, B, C, res)
    res4 = b.benchmark('mc_r_l_guid', mc_r_l_guid, A, B, C, res)
    logger.info('mc_r_l correctness: {}'.format(np.allclose(res3, res4)))

    A = np.random.randn(n, n)
    B = np.random.randn(n, n_5)
    C = np.random.randn(n_5, n)
    D = np.random.randn(n, n)
    res = np.zeros((A.shape[0], D.shape[1]), dtype=np.float64)
    res5 = b.benchmark('mc_mixed_orig', mc_mixed_orig, A, B, C, D, res)
    res6 = b.benchmark('mc_mixed_guid', mc_mixed_guid, A, B, C, D, res)
    logger.info('mc_mixed correctness: {}'.format(np.allclose(res5, res6)))
