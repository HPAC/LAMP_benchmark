from scipy import linalg
import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('CommonSubExpr')

@benchmark
def subexpr_nai(A, B):
    kt = A @ B + A @ B
    return kt

@benchmark
def subexpr_rec(A, B):
    kt = A @ B
    kt = kt + kt
    return kt


def exp09_common_subexpressions(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)

    res1 = b.benchmark('subexpr_nai', subexpr_nai, A, B)
    res2 = b.benchmark('subexpr_rec', subexpr_rec, A, B)
    logger.info('CommonSubExpr correctness: {}'.format(np.allclose(res1, res2)))
