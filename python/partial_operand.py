from scipy import linalg
import numpy as np
import logging
import time
import copy
from benchmarker import cache_scrub

logger = logging.getLogger('PartialOperand')

def par_op_ele_mult_nai(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = np.random.randn(A.shape[0])
    cache_scrub()
    start = time.perf_counter()
    ct = (at @ bt)[2, 2]
    end = time.perf_counter()

    return end-start, ct

def par_op_ele_add_nai(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = np.random.randn(A.shape[0])
    cache_scrub()
    start = time.perf_counter()
    ct = (at + bt)[2, 2]
    end = time.perf_counter()

    return end-start, ct


def par_op_ele_add_rec(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = np.random.randn(A.shape[0])
    cache_scrub()
    start = time.perf_counter()
    ct = at[2, 2] + bt[2, 2]
    end = time.perf_counter()

    return end-start, ct

def par_op_col_mult_nai(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = np.random.randn(A.shape[0])
    cache_scrub()
    start = time.perf_counter()
    ct = (at @ bt)[:, 2]
    end = time.perf_counter()

    return end-start, ct

def par_op_col_add_nai(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = np.random.randn(A.shape[0])
    cache_scrub()
    start = time.perf_counter()
    ct = (at + bt)[:, 2]
    end = time.perf_counter()

    return end-start, ct


def par_op_col_add_rec(A, B):

    at = copy.deepcopy(A)
    bt = copy.deepcopy(B)
    ct = np.random.randn(A.shape[0])
    cache_scrub()
    start = time.perf_counter()
    ct = at[:, 2] + bt[:, 2]
    end = time.perf_counter()

    return end-start, ct


def partial_operand(b, *args):

    res3 = b.benchmark('part_op_col_mult_nai', par_op_col_mult_nai, *args)
    res1 = b.benchmark('part_op_col_add_nai', par_op_col_add_nai, *args)
    res2 = b.benchmark('part_op_col_add_rec', par_op_col_add_rec, *args)
    logger.info('PartialOperand correctness: {}'.format(np.allclose(res1, res2)))

    res6 = b.benchmark('part_op_ele_mult_nai', par_op_ele_mult_nai, *args)
    res4 = b.benchmark('part_op_ele_add_nai', par_op_ele_add_nai, *args)
    res5 = b.benchmark('part_op_ele_add_rec', par_op_ele_add_rec, *args)
    logger.info('PartialOperand correctness: {}'.format(np.allclose(res4, res5)))
