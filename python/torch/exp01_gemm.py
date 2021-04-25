from benchmarker import benchmark
import logging
import torch as torch

logger = logging.getLogger('exp01_gemm')


@benchmark
def gemm_implicit_noup(A, B, C):
    C = A @ B
    return C


def exp01_gemm(b, n):
    A = torch.randn((n, n), dtype=torch.float64)
    B = torch.randn((n, n), dtype=torch.float64)
    C = torch.randn((n, n), dtype=torch.float64)

    res = b.benchmark('gemm_implicit_noup', gemm_implicit_noup, A, B, C)
