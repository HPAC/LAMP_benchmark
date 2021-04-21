import logging
from benchmarker import benchmark
import tensorflow as tf

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
    C = A @ tf.transpose(A) + C
    return C

@benchmark
def syrk_implicit_compact(A, C):
    C += A @ tf.transpose(A)
    return C

# from exp03_syr2k

@benchmark
def syr2k_implicit(A, B, C):
    C = A @ tf.transpose(B) + B @ tf.transpose(A) + C
    return C

@benchmark
def syr2k_implicit_compact(A, B, C):
    C += A @ tf.transpose(B) + B @ tf.transpose(A)
    return C

def exp04_update_of_c(b, n):

    A = tf.random.normal([n, n], dtype=tf.float64)
    B = tf.random.normal([n, n], dtype=tf.float64)
    C = tf.random.normal([n, n], dtype=tf.float64)

    b.benchmark('add', add, A, B)
    b.benchmark('scal', scal, A)

    # from exp01_gemm
    res1 = b.benchmark('gemm_implicit', gemm_implicit, A, B, C)
    res2 = b.benchmark('gemm_implicit_compact', gemm_implicit_compact, A, B, C)
    res3 = b.benchmark('gemm_implicit_coeff', gemm_implicit_coeff, A, B, C)
    res4 = b.benchmark('gemm_implicit_double_coeff', gemm_implicit_double_coeff, A, B, C)

    logger.info('Gemm correctness: {}'.format(tf.debugging.assert_near(res1, res2, rtol=1e-05, atol=1e-08)))

    # from exp02_syrk
    C = C + tf.transpose(C)

    res5 = b.benchmark('syrk_implicit', syrk_implicit, A, C)
    res6 = b.benchmark('syrk_implicit_compact', syrk_implicit_compact, A, C)

    logger.info('Syrk correctness: {}'.format(tf.debugging.assert_near(tf.linalg.band_part(res5, -1, 0), tf.linalg.band_part(res6, -1, 0)), rtol=1e-05, atol=1e-08))

    # from exp03_syr2k
    res7 = b.benchmark('syr2k_implicit', syr2k_implicit, A, B, C)
    res8 = b.benchmark('syr2k_implicit_compact', syr2k_implicit_compact, A, B, C)

    logger.info('Syr2k correctness: {}'.format(tf.debugging.assert_near(tf.linalg.band_part(res7, -1, 0), tf.linalg.band_part(res8, -1, 0)), rtol=1e-05, atol=1e-08))
