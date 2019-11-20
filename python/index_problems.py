from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('IndexProblems')


def index_problems(b, *args):

    res1 = b.benchmark("loop_nai", naive_loop, *args)
    res2 = b.benchmark("loop_rec", recommended_loop, *args)
    logger.info('IndexProblems correctness: {}'.format(np.allclose(res1, res2)))


def naive_loop(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()

    temp = np.zeros((A.shape[0], B.shape[1]), dtype=np.float64)
    for i in range(C.shape[0]):
        temp = at @ bt
        ct[i] = temp[i, i]
    end = time.perf_counter()
    return end-start, ct


def recommended_loop(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    temp = at @ bt
    for i in range(C.shape[0]):
        ct[i] = temp[i, i]
    end = time.perf_counter()
    return end-start, ct
