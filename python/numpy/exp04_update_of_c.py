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

@benchmark
def gemm_explicit(A, B, C):
    linalg.blas.dgemm(1.0, A, B, 1.0, C, trans_a=False, trans_b=False, overwrite_c=True)
    return C

# from exp02_syrk

@benchmark
def syrk_implicit(A, C):
    C = A @ A.T + C
    return C

@benchmark
def syrk_implicit_compact(A, C):
    C += A @ A.T
    return C

@benchmark
def syrk_explicit(A, C):
    linalg.blas.dsyrk(1.0, A, 1.0, C, overwrite_c=True, lower=True, trans=False)
    return C

# from exp03_syr2k

@benchmark
def syr2k_implicit(A, B, C):
    C = A @ B.T + B @ A.T + C
    return C

@benchmark
def syr2k_implicit_compact(A, B, C):
    C += A @ B.T + B @ A.T
    return C

@benchmark
def syr2k_explicit(A, B, C):
    linalg.blas.dsyr2k(1.0, A, B, 1.0, C, overwrite_c=True, lower=True, trans=False)
    return C

def exp04_update_of_c(b, n):

    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)
    C_fortran_style = C.ravel(order='F').reshape(C.shape, order='F')

    b.benchmark('add', add, A, B)
    b.benchmark('scal', scal, A)

    # from exp01_gemm
    res01 = b.benchmark('gemm_implicit', gemm_implicit, A, B, C)
    res02 = b.benchmark('gemm_implicit_compact', gemm_implicit_compact, A, B, C)
    res03 = b.benchmark('gemm_explicit', gemm_explicit, A, B, C_fortran_style)
    res04 = b.benchmark('gemm_implicit_coeff', gemm_implicit_coeff, A, B, C)
    res05 = b.benchmark('gemm_implicit_double_coeff', gemm_implicit_double_coeff, A, B, C)

    logger.info('Gemm correctness: {}'.format(np.allclose(res01, res02)))
    logger.info('Gemm correctness: {}'.format(np.allclose(res01, res03)))

    # from exp02_syrk
    C = C + C.T
    C_fortran_style = C.ravel(order='F').reshape(C.shape, order='F')

    res06 = b.benchmark('syrk_implicit', syrk_implicit, A, C)
    res07 = b.benchmark('syrk_implicit_compact', syrk_implicit_compact, A, C)
    res08 = b.benchmark('syrk_explicit', syrk_explicit, A, C_fortran_style)

    logger.info('Syrk correctness: {}'.format(np.allclose(np.tril(res06, k=0), np.tril(res07, k=0))))
    logger.info('Syrk correctness: {}'.format(np.allclose(np.tril(res06, k=0), np.tril(res08, k=0))))

    # from exp03_syr2k
    res09 = b.benchmark('syr2k_implicit', syr2k_implicit, A, B, C)
    res10 = b.benchmark('syr2k_implicit_compact', syr2k_implicit_compact, A, B, C)
    res11 = b.benchmark('syr2k_explicit', syr2k_explicit, A, B, C_fortran_style)

    logger.info('Syr2k correctness: {}'.format(np.allclose(np.tril(res09, k=0), np.tril(res10, k=0))))
    logger.info('Syr2k correctness: {}'.format(np.allclose(np.tril(res09, k=0), np.tril(res11, k=0))))
