import os
import numpy as np
import gc
gc.disable()

from benchmarker import Benchmarker as ben
from kernel_invocations_syrk import kernel_invocations_syrk
from kernel_invocations_gemm import exp01_gemm
from kernel_invocations_syr2k import kernel_invocations_syr2k
from transposition import transposition
from solve_linear_systems import solve_linear_systems
from matrix_chain import matrix_chain
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

A = np.random.randn(n, n)
B = np.random.randn(n, n)
add_scal(b, A, B)

# ! Properties Solve

properties_solve(b, n, 200)

# ! SYRK

A = np.random.randn(n, n)
C = np.random.randn(n, n)
C = C + C.T

kernel_invocations_syrk(b, A, C)



# ! SYR2K

A = np.random.randn(n, n)
B = np.random.randn(n, n)
C = np.random.randn(n, n)
C = C + C.T

kernel_invocations_syr2k(b, A, B, C)

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

A = np.random.randn(n, n)
B = np.random.randn(n, 200)

solve_linear_systems(b, A, B)

#! Matrix Chain Problem

A = np.random.randn(n, n)
B = np.random.randn(n, n)

matrix_chain(b, A, B)

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

print (Here, we commit the first change.)