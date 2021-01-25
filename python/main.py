import os
import numpy as np
import gc
gc.disable()

from benchmarker import Benchmarker as ben
from exp02_syrk import exp02_syrk
from exp01_gemm import exp01_gemm
from exp03_syr2k import exp03_syr2k
from transposition import transposition
from exp05_explicit_inversion import exp05_explicit_inversion
from exp06_optimal_parenthesization import exp06_optimal_parenthesization
from diagonal_elements import diagonal_elements
from common_subexpressions import common_subexpressions
from index_problems import index_problems
from partitioned_matrices import partitioned_matrices
from loop_translation import loop_translation
from properties_solve import properties_solve
from partial_operand import partial_operand
from add_scal import add_scal
import logging

logging.basicConfig(level=logging.INFO, format='%(name)-2s: %(levelname)-2s %(message)s')
logger = logging.getLogger('Main')
# logger.info('Numpy version: {}'.format(np.__version__))
# print('{}'.format(np.__config__.show()))

n = int(os.environ['LAMP_N'])

b = ben('python_' + str(os.environ['OMP_NUM_THREADS']))

# ! GEMM

exp01_gemm(b, n)

# add_scal
A = np.random.randn(n, n)
B = np.random.randn(n, n)
add_scal(b, A, B)

# ! Properties Solve

properties_solve(b, n, 200)

# ! SYRK

exp02_syrk(b, n)

# ! SYR2K

exp03_syr2k(b, n)

# ! Transposition

tn = int(n / 10)
A = np.random.randn(tn, tn)
B = np.random.randn(tn, tn)
C = np.random.randn(tn, tn)

transposition(b, A, B, C)

# ! Common Subexpression

A = np.random.randn(n, n)
B = np.random.randn(n, n)

common_subexpressions(b, A, B)

# ! Composed Operations

exp05_explicit_inversion(b, n)

#! Matrix Chain Problem

exp06_optimal_parenthesization(b, A, B)

# ! Diagonal elements

A = np.random.randn(n, n)
B = np.random.randn(n, n)

diagonal_elements(b, A, B)

# ! Partial Operand

A = np.random.randn(n, n)
B = np.random.randn(n, n)

partial_operand(b, A, B)

# ! Index problems

ipn = int(n / 10)
A = np.random.randn(ipn, ipn)
B = np.random.randn(ipn, ipn)
C = np.random.randn(ipn)

index_problems(b, A, B, C)

# ! Index problems

A = np.random.randn(n, n)
B = np.random.randn(n, n)
C = np.random.randn(n, n)

loop_translation(b, A, B, C)

# ! Partitioned Matrices

p = int(n / 2)
A1 = np.random.randn(p, p)
A2 = np.random.randn(p, p)
B = np.random.randn(2*p, 2*p)

partitioned_matrices(b, A1, A2, B)
