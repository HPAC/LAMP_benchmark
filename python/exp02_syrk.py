import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp02_syrk')

@benchmark
def syrk_implicit_noup(A, C):
    C = A @ torch.transpose(A, 0, 1)
    return C


def exp02_syrk(b, n):

    A = torch.randn(n, n)
    C = torch.randn(n, n)
    C = C + torch.transpose(C, 0, 1)

    res = b.benchmark('syrk_implicit_noup', syrk_implicit_noup, A, C)
