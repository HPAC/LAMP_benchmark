from benchmarker import cache_scrub
from scipy.sparse.linalg import spsolve
import scipy.sparse as sp
import numpy as np
import logging
import time
import copy

logger = logging.getLogger('PropertiesSolveSparse')

def my_solve(A, B):

    logger.info("iteration")
    ct = np.zeros(B.shape)
    cache_scrub()
    start = time.perf_counter()
    ct = spsolve(A, B)
    end = time.perf_counter()
    return end-start, ct


def properties_solve_sparse(b, n, rhs, density):

    B = np.random.randn(n, rhs)

    # General
    A = sp.random(n, n, density=density, format='csc', data_rvs=np.random.randn) + sp.eye(n)
    logger.info('onenormest: {:.1f}, nnz: {}'.format(sp.linalg.onenormest(A), A.nnz))
    b.benchmark('solve_sp_gen', my_solve, A, B)

    # Symmetric
    A = sp.random(n, n, density=density/2.0, format='csc', data_rvs=np.random.randn)
    A = A + A.T + 2.0 * sp.eye(n)
    logger.info('onenormest: {:.1f}, nnz: {}'.format(sp.linalg.onenormest(A), A.nnz))
    b.benchmark('solve_sp_sym', my_solve, A, B)

    # SPD
    A = sp.random(n, n, density=density/2.0, format='csc', data_rvs=np.random.randn)
    A = A + A.transpose() + n * sp.eye(n)
    logger.info('onenormest: {:.1f}, nnz: {}'.format(sp.linalg.onenormest(A), A.nnz))
    b.benchmark('solve_sp_spd', my_solve, A, B)
