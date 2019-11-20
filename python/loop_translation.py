from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('LoopTranslation')


def loop_translation(b, *args):

    res1 = b.benchmark("loop_translation_nai", naive_loop, *args)
    res2 = b.benchmark("loop_translation_rec", recommended_loop, *args)
    logger.info('LoopTranslation correctness: {}'.format(np.allclose(res1, res2)))


def naive_loop(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()

    for i in range(C.shape[1]):
        ct[:, i] = at @ bt[:, i]
    end = time.perf_counter()
    return end-start, ct


def recommended_loop(A, B, C):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = copy.deepcopy(C)
    cache_scrub()
    start = time.perf_counter()
    ct = at @ bt
    end = time.perf_counter()
    return end-start, ct
