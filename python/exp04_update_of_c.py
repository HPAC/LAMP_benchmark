import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp04_update_of_c')

@benchmark
def add(A, B):
    B = A + B
    return B

@benchmark
def scal(A):
    A = 3.0 * A
    return A

# from exp01_gemm

@benchmark
def gemm_implicit(A, B, C):
    C = A @ B + C
    return C

@benchmark
def gemm_implicit_compact(A, B, C):
    C += A @ B
    return C

@benchmark
def gemm_implicit_coeff(A, B, C):
    C = 3.0 * A @ B + C
    return C

@benchmark
def gemm_implicit_double_coeff(A, B, C):
    C = 3.0 * A @ B + 3.0 * C
    return C

# from exp02_syrk

@benchmark
def syrk_implicit(A, C):
    C = A @ torch.transpose(A, 0, 1) + C
    return C

@benchmark
def syrk_implicit_compact(A, C):
    C += A @ torch.transpose(A, 0, 1)
    return C

# from exp03_syr2k

@benchmark
def syr2k_implicit(A, B, C):
    C = A @ torch.transpose(B, 0, 1) + B @ torch.transpose(A, 0, 1) + C
    return C

@benchmark
def syr2k_implicit_compact(A, B, C):
    C += A @ torch.transpose(B, 0, 1) + B @ torch.transpose(A, 0, 1)
    return C

def exp04_update_of_c(b, n):

    A = torch.randn(n, n)
    B = torch.randn(n, n)
    C = torch.randn(n, n)

    b.benchmark('add', add, A, B)
    b.benchmark('scal', scal, A)

    # from exp01_gemm
    res1 = b.benchmark('gemm_implicit', gemm_implicit, A, B, C)
    res2 = b.benchmark('gemm_implicit_compact', gemm_implicit_compact, A, B, C)
    res3 = b.benchmark('gemm_implicit_coeff', gemm_implicit_coeff, A, B, C)
    res4 = b.benchmark('gemm_implicit_double_coeff', gemm_implicit_double_coeff, A, B, C)

    logger.info('Gemm correctness: {}'.format(torch.allclose(res1, res2)))

    # from exp02_syrk
    C = C + torch.transpose(C, 0, 1)

    res5 = b.benchmark('syrk_implicit', syrk_implicit, A, C)
    res6 = b.benchmark('syrk_implicit_compact', syrk_implicit_compact, A, C)

    logger.info('Syrk correctness: {}'.format(torch.allclose(torch.tril(res5), torch.tril(res6))))

    # from exp03_syr2k
    res7 = b.benchmark('syr2k_implicit', syr2k_implicit, A, B, C)
    res8 = b.benchmark('syr2k_implicit_compact', syr2k_implicit_compact, A, B, C)

    logger.info('Syr2k correctness: {}'.format(torch.allclose(torch.tril(res7), torch.tril(res8))))
