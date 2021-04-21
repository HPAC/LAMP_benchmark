import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp03_syr2k')

@benchmark
def syr2k_implicit_noup(A, B, C):
    C = A @ torch.transpose(B, 0, 1) + B @ torch.transpose(A, 0, 1)
    return C


def exp03_syr2k(b, n):

    A = torch.randn((n, n), dtype=torch.float64)
    B = torch.randn((n, n), dtype=torch.float64)
    C = torch.randn((n, n), dtype=torch.float64)
    C = C + torch.transpose(C, 0, 1)

    res = b.benchmark('syr2k_implicit_noup', syr2k_implicit_noup, A, B, C)
