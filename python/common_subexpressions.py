from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('CommonSubExpr')


def subexpr_nai(A, B):

    cache_scrub()
    start = time.perf_counter()
    kt = A @ B + A @ B
    end = time.perf_counter()

    return end-start, kt


def subexpr_rec(A, B):

    cache_scrub()
    start = time.perf_counter()
    kt = A @ B
    kt = kt + kt
    end = time.perf_counter()

    return end-start, kt


def common_subexpressions(b, *args):

    res1 = b.benchmark('subexpr_nai', subexpr_nai, *args)
    res2 = b.benchmark('subexpr_rec', subexpr_rec, *args)
    logger.info('CommonSubExpr correctness: {}'.format(np.allclose(res1, res2)))
