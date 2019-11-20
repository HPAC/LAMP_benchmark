from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('Partitioned Matrices')


def partitioned_matrices(b, *args):
    res1 = b.benchmark("compact", blocked_solve_naive, *args)
    res2 = b.benchmark("blocked", blocked_solve_recommended, *args)
    logger.info('PartitionedMatrices correctness: {}'.format(np.allclose(res1, res2)))


def blocked_solve_naive(A1, A2, B):
    a1t = copy.deepcopy(A1)
    a2t = copy.deepcopy(A2)
    bt = copy.deepcopy(B)

    cache_scrub()
    start = time.perf_counter()

    ct = np.zeros((B.shape[0], B.shape[1]), dtype=np.float64)
    ct = np.linalg.solve(np.concatenate(
        (np.concatenate((a1t, np.zeros((A1.shape[0], A1.shape[1]), dtype=np.float64)), axis=1),
         np.concatenate((np.zeros((A2.shape[0], A2.shape[1]), dtype=np.float64), a2t), axis=1)), axis=0), bt)
    end = time.perf_counter()
    return end-start, ct


def blocked_solve_recommended(A1, A2, B):
    a1t = copy.deepcopy(A1)
    a2t = copy.deepcopy(A2)
    bt = copy.deepcopy(B)

    cache_scrub()
    start = time.perf_counter()

    b1 = bt[0:a1t.shape[0], 0:bt.shape[1]]
    b2 = bt[a1t.shape[0]:, 0:bt.shape[1]]
    # print("b1_1: {}".format(b1_1.shape))
    # print("b1_2: {}".format(b1_2.shape))
    # print("b2_1: {}".format(b2_1.shape))
    # print("b2_2: {}".format(b2_2.shape))
    ct = np.concatenate((np.linalg.solve(a1t, b1), np.linalg.solve(a2t, b2)), axis=0)
    end = time.perf_counter()
    return end-start, ct
