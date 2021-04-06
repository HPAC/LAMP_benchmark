import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp05_explicit_inversion')

@benchmark
def solve_nai(A, B):
    C = torch.linalg.inv(A) @ B
    return C

@benchmark
def solve_rec(A, B):
    C = torch.linalg.solve(A, B)
    return C


def exp05_explicit_inversion(b, n):

    A = torch.randn((n, n), dtype=torch.float64)
    B = torch.randn((n, 200), dtype=torch.float64)

    res1 = b.benchmark('solve_nai', solve_nai, A, B)
    res2 = b.benchmark('solve_rec', solve_rec, A, B)
    logger.info('Solve correctness: {}'.format(torch.allclose(res1, res2)))

    B = torch.randn((n, 5*n), dtype=torch.float64)  # B.rows , 5 * A.rows
    res3 = b.benchmark('solve_large_nai', solve_nai, A, B)
    res4 = b.benchmark('solve_large_rec', solve_rec, A, B)
    logger.info('Solve correctness: {}'.format(torch.allclose(res3, res4)))
