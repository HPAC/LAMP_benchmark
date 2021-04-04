import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp09_common_subexpressions')

@benchmark
def subexpr_nai(A, B, K):
    K = A @ B + A @ B
    return K

@benchmark
def subexpr_rec(A, B, K):
    K = A @ B
    K = K + K
    return K


def exp09_common_subexpressions(b, n):

    A = torch.randn(n, n)
    B = torch.randn(n, n)
    K = torch.zeros((n, n), dtype=torch.float64)

    res1 = b.benchmark('subexpr_nai', subexpr_nai, A, B, K)
    res2 = b.benchmark('subexpr_rec', subexpr_rec, A, B, K)
    logger.info('CommonSubExpr correctness: {}'.format(torch.allclose(res1, res2)))
