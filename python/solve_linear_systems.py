from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('Solve')


def solve_nai(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(B)
    cache_scrub()
    start = time.perf_counter()
    ct = np.linalg.inv(at) @ bt
    end = time.perf_counter()

    return end-start, ct


def solve_rec(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(B)
    cache_scrub()
    start = time.perf_counter()
    ct = np.linalg.solve(at, bt)
    end = time.perf_counter()
    return end-start, ct


def solve_linear_systems(b, *args):

    res1 = b.benchmark('solve_nai', solve_nai, *args)
    res2 = b.benchmark('solve_rec', solve_rec, *args)
    logger.info('Solve correctness: {}'.format(np.allclose(res1, res2)))

    A = args[0]
    B = np.random.randn(args[1].shape[0], 2 * args[0].shape[0])  # B.rows , 2 * A.rows
    res3 = b.benchmark('solve_large_nai', solve_nai, A, B)
    res4 = b.benchmark('solve_large_rec', solve_rec, A, B)
    logger.info('Solve correctness: {}'.format(np.allclose(res3, res4)))
