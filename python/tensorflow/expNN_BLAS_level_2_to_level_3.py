import logging
from benchmarker import benchmark
import numpy as np

logger = logging.getLogger('expNN_BLAS_level_2_to_level_3')


@benchmark
def naive_loop(A, B, C):
    for i in range(C.shape[1]):
        C[:, i] = A @ B[:, i]
    return C


@benchmark
def recommended_loop(A, B, C):
    C = A @ B
    return C


def expNN_BLAS_level_2_to_level_3(b, n):
    A = np.random.randn(n, n)
    B = np.random.randn(n, n)
    C = np.random.randn(n, n)

    res1 = b.benchmark("loop_translation_nai", naive_loop, A, B, C)
    res2 = b.benchmark("loop_translation_rec", recommended_loop, A, B, C)
    logger.info('LoopTranslation correctness: {}'.format(np.allclose(res1, res2)))
