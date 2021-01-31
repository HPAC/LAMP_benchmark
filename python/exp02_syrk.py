from scipy import linalg
import numpy as np
import logging
from benchmarker import benchmark

logger = logging.getLogger('exp02_syrk')

@benchmark
def syrk_implicit_noup(A, C):
    C = A @ A.T
    return C


def exp02_syrk(b, n):

    A = np.random.randn(n, n)
    C = np.random.randn(n, n)
    C = C + C.T

    res1 = b.benchmark('syrk_implicit_noup', syrk_implicit_noup, A, C)

