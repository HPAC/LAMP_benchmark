import copy
import logging
from benchmarker import benchmark
import tensorflow as tf

logger = logging.getLogger('exp12_partial_operand_access')

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

@benchmark
def diagonal_mult_nai(A, B, C):
    C = tf.experimental.numpy.diagonal(A @ B)
    return C

@benchmark
def diagonal_nai(A, B, C):
    C = tf.experimental.numpy.diagonal(A + B)
    return C

@benchmark
def diagonal_rec(A, B, C):
    C = tf.experimental.numpy.diagonal(A) + tf.experimental.numpy.diagonal(B)
    return C


def exp12_partial_operand_access(b, n):

    A = tf.random.normal([n, n])
    B = tf.random.normal([n, n])
    C = tf.random.normal([n])

    res3 = b.benchmark('part_op_col_mult_nai', par_op_col_mult_nai,  A, B, C)
    res1 = b.benchmark('part_op_col_add_nai', par_op_col_add_nai,  A, B, C)
    res2 = b.benchmark('part_op_col_add_rec', par_op_col_add_rec,  A, B, C)
    logger.info('PartialOperand correctness: {}'.format(tf.experimental.numpy.allclose(res1, res2)))

    C = tf.random.normal([1])
    res6 = b.benchmark('part_op_ele_mult_nai', par_op_ele_mult_nai,  A, B, C)
    res4 = b.benchmark('part_op_ele_add_nai', par_op_ele_add_nai,  A, B, C)
    res5 = b.benchmark('part_op_ele_add_rec', par_op_ele_add_rec,  A, B, C)
    logger.info('PartialOperand correctness: {}'.format(tf.experimental.numpy.allclose(res4, res5)))

    C = copy.deepcopy(B)
    C = tf.experimental.numpy.diagonal(C)
    res9 = b.benchmark('diag_mult_nai', diagonal_mult_nai, A, B, C)
    res7 = b.benchmark('diag_add_nai', diagonal_nai, A, B, C)
    res8 = b.benchmark('diag_add_rec', diagonal_rec, A, B, C)
    logger.info('PartialOperand correctness: {}'.format(tf.experimental.numpy.allclose(res7, res8)))
