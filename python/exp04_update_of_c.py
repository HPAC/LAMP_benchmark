import logging
import numpy as np
from scipy import linalg
from benchmarker import benchmark

logger = logging.getLogger('exp04_update_of_c')

@benchmark
def add(A, B):
    B = A + B
    return B

@benchmark
def scal(A):
    A = 3.0 * A
    return A



def exp04_update_of_c(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)

    b.benchmark('add', add, A, B)
    b.benchmark('scal', scal, A)
