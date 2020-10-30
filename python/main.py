import numpy as np
from benchmarker import Benchmarker as ben
from kernel_invocations_syrk import kernel_invocations_syrk
from kernel_invocations_gemm import kernel_invocations_gemm
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

m = 3000
k = 550
n = 3000

tn = 80
ipn = 80
l = 100
p = 1500

b = ben('python_' + str(os.environ['OMP_NUM_THREADS']))

A = np.random.randn(n, n)
B = np.random.randn(n, n)
add_scal(b, A, B)

# ! Properties Solve

properties_solve(b, m, l)

# ! SYRK

A = np.random.randn(n, k)
C = np.random.randn(n, n)
C = C + C.T

kernel_invocations_syrk(b, A, C)

# ! GEMM

A = np.random.randn(m, k)
B = np.random.randn(k, n)
C = np.random.randn(m, n)

kernel_invocations_gemm(b, A, B, C)

# ! SYR2K

A = np.random.randn(n, k)
B = np.random.randn(n, k)
C = np.random.randn(n, n)
C = C + C.T

kernel_invocations_syr2k(b, A, B, C)

# ! Transposition

A = np.random.randn(tn, tn)
B = np.random.randn(tn, tn)
C = np.random.randn(tn, tn)

transposition(b, A, B, C)

# ! Common Subexpression

A = np.random.randn(m, k)
B = np.random.randn(k, n)

common_subexpressions(b, A, B)

# ! Composed Operations

A = np.random.randn(n, n)
B = np.random.randn(n, l)

solve_linear_systems(b, A, B)

#! Matrix Chain Problem

A = np.random.randn(m, k)
B = np.random.randn(k, n)

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

A1 = np.random.randn(p, p)
A2 = np.random.randn(p, p)
B = np.random.randn(2*p, 2*p)

partitioned_matrices(b, A1, A2, B)
