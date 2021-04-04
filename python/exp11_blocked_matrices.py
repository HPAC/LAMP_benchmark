import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp11_blocked_matrices')

@benchmark
def blocked_solve_naive(A1, A2, B, C):
    C = torch.linalg.solve(torch.cat(
        (torch.cat((A1, torch.zeros((A1.shape[0], A1.shape[1]), dtype=torch.float64)), dim=1),
         torch.cat((torch.zeros((A2.shape[0], A2.shape[1]), dtype=torch.float64), A2), dim=1)), dim=0), B)
    return C

@benchmark
def blocked_solve_recommended(A1, A2, B, C):
    b1 = B[0:A1.shape[0], 0:B.shape[1]]
    b2 = B[A1.shape[0]:, 0:B.shape[1]]
    C = torch.cat((torch.linalg.solve(A1, b1), torch.linalg.solve(A2, b2)), dim=0)
    return C

def exp11_blocked_matrices(b, n):

    bm_n = int(n / 2)
    A1 = torch.randn(bm_n, bm_n)
    A2 = torch.randn(bm_n, bm_n)
    B = torch.randn(2 * bm_n, 2 * bm_n)
    C = torch.zeros((2 * bm_n, 2 * bm_n), dtype=torch.float64)

    res1 = b.benchmark("compact", blocked_solve_naive, A1, A2, B, C)
    res2 = b.benchmark("blocked", blocked_solve_recommended, A1, A2, B, C)
    logger.info('PartitionedMatrices correctness: {}'.format(torch.allclose(res1, res2)))
