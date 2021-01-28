import os
import numpy as np
import gc
gc.disable()

from benchmarker import Benchmarker as ben

from exp01_gemm import exp01_gemm
from exp02_syrk import exp02_syrk
from exp03_syr2k import exp03_syr2k
# from exp04_update_of_c import exp04_update_of_c
from exp05_explicit_inversion import exp05_explicit_inversion
from exp06_optimal_parenthesization import exp06_optimal_parenthesization
from exp07_properties_multiplication import exp07_properties_multiplication
from exp08_properties_in_linear_systems import exp08_properties_in_linear_systems
from exp09_common_subexpressions import exp09_common_subexpressions
from exp10_loop_invariant_code_motion import exp10_loop_invariant_code_motion
from exp11_blocked_matrices import exp11_blocked_matrices
from exp12_partial_operand_access import exp12_partial_operand_access

from loop_translation import loop_translation
from add_scal import add_scal
from transposition import transposition

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
exp08_properties_in_linear_systems(b, n, 200)

# ! SYRK
exp02_syrk(b, n)

# ! SYR2K
exp03_syr2k(b, n)

# ! Transposition
tn = int(n / 10)
A = np.random.randn(tn, tn)
B = np.random.randn(tn, tn)
C = np.random.randn(tn, tn)

transposition(b, n)

# ! Common Subexpression
exp09_common_subexpressions(b, n)

# ! Composed Operations
exp05_explicit_inversion(b, n)

#! Matrix Chain Problem
exp06_optimal_parenthesization(b, n)

# ! Partial Operand
exp12_partial_operand_access(b, n)

# ! Index problems
exp10_loop_invariant_code_motion(b, n)

# ! Index problems
A = np.random.randn(n, n)
B = np.random.randn(n, n)
C = np.random.randn(n, n)

loop_translation(b, A, B, C)

# ! Partitioned Matrices
exp11_blocked_matrices(b, n)
