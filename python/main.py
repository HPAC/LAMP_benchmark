import os
import gc
gc.disable()

from benchmarker import Benchmarker as ben

from exp01_gemm import exp01_gemm
from exp02_syrk import exp02_syrk
from exp03_syr2k import exp03_syr2k
from exp04_update_of_c import exp04_update_of_c
from exp05_explicit_inversion import exp05_explicit_inversion
from exp06_optimal_parenthesization import exp06_optimal_parenthesization
from exp07_properties_multiplication import exp07_properties_multiplication
from exp08_properties_in_linear_systems import exp08_properties_in_linear_systems
from exp09_common_subexpressions import exp09_common_subexpressions
from exp10_loop_invariant_code_motion import exp10_loop_invariant_code_motion
from exp11_blocked_matrices import exp11_blocked_matrices
from exp12_partial_operand_access import exp12_partial_operand_access
from expNN_BLAS_level_2_to_level_3 import expNN_BLAS_level_2_to_level_3
from expNN_transposition import expNN_transposition

import logging

logging.basicConfig(level=logging.INFO, format='%(name)-2s: %(levelname)-2s %(message)s')
logger = logging.getLogger('Main')
# logger.info('Numpy version: {}'.format(np.__version__))
# print('{}'.format(np.__config__.show()))

n = int(os.environ['LAMP_N'])

b = ben('python_' + str(os.environ['OMP_NUM_THREADS']))
"""
exp01_gemm(b, n)

exp02_syrk(b, n)

exp03_syr2k(b, n)

exp04_update_of_c(b, n)

exp05_explicit_inversion(b, n)
"""
exp06_optimal_parenthesization(b, n)
"""
exp07_properties_multiplication(b, n)

exp08_properties_in_linear_systems(b, n, 200)

exp09_common_subexpressions(b, n)

exp10_loop_invariant_code_motion(b, n)

exp11_blocked_matrices(b, n)

exp12_partial_operand_access(b, n)

expNN_BLAS_level_2_to_level_3(b, n)

expNN_transposition(b, n)
"""