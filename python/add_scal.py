from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('AddScal')


def add(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    cache_scrub()
    start = time.perf_counter()
    bt = at + bt
    end = time.perf_counter()

    return end-start, [bt]


def scal(A, B):

    at = copy.deepcopy(A)
    cache_scrub()
    start = time.perf_counter()
    at = 3.0 * at
    end = time.perf_counter()

    return end-start, [at]


def add_scal(b, *args):

    b.benchmark('add', add, *args)
    b.benchmark('scal', scal, *args)
