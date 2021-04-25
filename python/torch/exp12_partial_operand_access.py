import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp12_partial_operand_access')


@benchmark
def par_op_ele_mult_nai(A, B, c):
    c = (A @ B)[2, 2]
    return c


@benchmark
def par_op_ele_add_nai(A, B, c):
    c = (A + B)[2, 2]
    return c


@benchmark
def par_op_ele_add_rec(A, B, c):
    c = A[2, 2] + B[2, 2]
    return c


@benchmark
def par_op_col_mult_nai(A, B, c):
    c = (A @ B)[:, 2]
    return c


@benchmark
def par_op_col_add_nai(A, B, c):
    c = (A + B)[:, 2]
    return c


@benchmark
def par_op_col_add_rec(A, B, c):
    c = A[:, 2] + B[:, 2]
    return c


@benchmark
def diagonal_mult_nai(A, B, c):
    c = torch.diagonal(A @ B)
    return c


@benchmark
def diagonal_nai(A, B, c):
    c = torch.diagonal(A + B)
    return c


@benchmark
def diagonal_rec(A, B, c):
    c = torch.diagonal(A) + torch.diagonal(B)
    return c


def exp12_partial_operand_access(b, n):
    A = torch.randn((n, n), dtype=torch.float64)
    B = torch.randn((n, n), dtype=torch.float64)
    c = torch.randn(n, dtype=torch.float64)

    res3 = b.benchmark('part_op_col_mult_nai', par_op_col_mult_nai, A, B, c)
    res1 = b.benchmark('part_op_col_add_nai', par_op_col_add_nai, A, B, c)
    res2 = b.benchmark('part_op_col_add_rec', par_op_col_add_rec, A, B, c)
    logger.info('PartialOperand correctness: {}'.format(torch.allclose(res1, res2)))

    c = torch.randn(1, dtype=torch.float64)
    res6 = b.benchmark('part_op_ele_mult_nai', par_op_ele_mult_nai, A, B, c)
    res4 = b.benchmark('part_op_ele_add_nai', par_op_ele_add_nai, A, B, c)
    res5 = b.benchmark('part_op_ele_add_rec', par_op_ele_add_rec, A, B, c)
    logger.info('PartialOperand correctness: {}'.format(torch.allclose(res4, res5)))

    c = torch.randn(n, dtype=torch.float64)
    res9 = b.benchmark('diag_mult_nai', diagonal_mult_nai, A, B, c)
    res7 = b.benchmark('diag_add_nai', diagonal_nai, A, B, c)
    res8 = b.benchmark('diag_add_rec', diagonal_rec, A, B, c)
    logger.info('PartialOperand correctness: {}'.format(torch.allclose(res7, res8)))
