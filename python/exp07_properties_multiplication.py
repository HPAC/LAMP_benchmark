from benchmarker import benchmark
import logging
import torch as torch

logger = logging.getLogger('exp07_properties_multiplication')

@benchmark
def trmm_implicit(A, B):
    B = A @ B
    return B

@benchmark
def diagmm(A, B, C):
    C = A @ B
    return C


def exp07_properties_multiplication(b, n):

    A = torch.randn(n, n)
    B = torch.randn(n, n)
    C = torch.randn(n, n)

    A = torch.tril(A)
    logger.debug('A is triangualar'.format(torch.allclose(A, torch.tril(A))))
    res1 = b.benchmark('trmm_implicit', trmm_implicit, A, B)

    Ad = torch.diag(torch.diag(A))
    res2 = b.benchmark('diagmm', diagmm, Ad, B, C)
