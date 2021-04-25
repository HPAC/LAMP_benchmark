import logging
from benchmarker import benchmark
import torch as torch

logger = logging.getLogger('exp08_properties_in_linear_systems')


@benchmark
def solve(A, B, C):
    C = torch.linalg.solve(A, B)
    return C


def exp08_properties_in_linear_systems(b, n, rhs):
    B = torch.randn((n, rhs), dtype=torch.float64)
    C = torch.zeros((n, rhs), dtype=torch.float64)

    # SPD
    A = torch.randn((n, n), dtype=torch.float64)
    A = A + torch.transpose(A, 0, 1) + torch.eye(n, dtype=torch.float64) * n
    logger.info('A is symmetric: {}'.format(torch.allclose(A, torch.transpose(A, 0, 1))))
    try:
        torch.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except RuntimeError:
        logger.info('A is SPD: False')
    b.benchmark('solve_spd', solve, A, B, C)

    # Symmetric
    A = torch.randn((n, n), dtype=torch.float64)
    A = A + torch.transpose(A, 0, 1)
    A[1, 1] = -1.0
    logger.info('A is symmetric: {}'.format(torch.allclose(A, torch.transpose(A, 0, 1))))
    try:
        torch.linalg.cholesky(A)
        logger.info('A is SPD: True')
    except RuntimeError:
        logger.info('A is SPD: False')
    b.benchmark('solve_sym', solve, A, B, C)

    # Triangular
    A = torch.randn((n, n), dtype=torch.float64)
    A = torch.tril(A)
    logger.info('A is triangular: {}'.format(torch.allclose(A, torch.tril(A))))
    b.benchmark('solve_tri', solve, A, B, C)

    # Diagonal
    A = torch.randn((n, n), dtype=torch.float64)
    A = torch.diag(torch.diag(A))
    logger.info('A is diagonal: {}'.format(torch.allclose(A, torch.diag(torch.diag(A)))))
    b.benchmark('solve_dia', solve, A, B, C)
