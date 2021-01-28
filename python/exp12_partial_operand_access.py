from scipy import linalg
import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('PartialOperand')

@benchmark
def par_op_ele_mult_nai(A, B, C):
    C = (A @ B)[2, 2]
    return C

@benchmark
def par_op_ele_add_nai(A, B, C):
    C = (A + B)[2, 2]
    return C

@benchmark
def par_op_ele_add_rec(A, B, C):
    C = A[2, 2] + B[2, 2]
    return C

@benchmark
def par_op_col_mult_nai(A, B, C):
    C = (A @ B)[:, 2]
    return C

@benchmark
def par_op_col_add_nai(A, B, C):
    C = (A + B)[:, 2]
    return C


@benchmark
def par_op_col_add_rec(A, B, C):
    C = A[:, 2] + B[:, 2]
    return C


def exp12_partial_operand_access(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n)

    res3 = b.benchmark('part_op_col_mult_nai', par_op_col_mult_nai,  A, B, C)
    res1 = b.benchmark('part_op_col_add_nai', par_op_col_add_nai,  A, B, C)
    res2 = b.benchmark('part_op_col_add_rec', par_op_col_add_rec,  A, B, C)
    logger.info('PartialOperand correctness: {}'.format(np.allclose(res1, res2)))

    res6 = b.benchmark('part_op_ele_mult_nai', par_op_ele_mult_nai,  A, B, C)
    res4 = b.benchmark('part_op_ele_add_nai', par_op_ele_add_nai,  A, B, C)
    res5 = b.benchmark('part_op_ele_add_rec', par_op_ele_add_rec,  A, B, C)
    logger.info('PartialOperand correctness: {}'.format(np.allclose(res4, res5)))
