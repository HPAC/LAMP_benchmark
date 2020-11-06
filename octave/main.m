addpath(getenv('LAMP_OCTAVE_DIR'))
import MatrixGenerator.Benchmarker;

n = str2num(getenv('LAMP_N'));

b = Benchmarker();

A = randn(n,n);
B = randn(n,n);
add_scal(A, B, b);

properties_solve(n, n / 10, b);

A = randn(n,n);
C = randn(n,n); C = C+C';
kernel_invocations_syrk(A, C, b);

A = randn(n,n);
B = randn(n,n);
C = randn(n,n);
kernel_invocations_gemm(A, B, C, b);

A = randn(n,n);
B = randn(n,n);
C = randn(n,n); C = C+C';
kernel_invocations_syr2k(A, B, C, b);

A = randn(n / 10, n / 10);
B = randn(n / 10, n / 10);
C = randn(n / 10, n / 10);
transposition(A, B, C, b);

A = randn(n,n);
B = randn(n,n);
common_subexpressions(A, B, b);

A = randn(n,n);
B = randn(n,n / 10);
solve_linear_systems(A, B, b);

A = randn(n,n);
B = randn(n,n);
matrix_chain(A, B, b);

A = randn(n,n);
B = randn(n,n);
diagonal_elements(A, B, b);

A = randn(n,n);
B = randn(n,n);
partial_operand(A, B, b);

A = randn(n / 10,n / 10);
B = randn(n / 10,n / 10);
C = randn(n / 10,1);
index_problems(A, B, C, b);

A = randn(n,n);
B = randn(n,n);
C = randn(n,n);
loop_translation(A, B, C, b);

A1 = randn(n / 10,n / 10);
A2 = randn(n / 10,n / 10);
B = randn(n / 5,n / 5);
partitioned_matrices(A1, A2, B, b);

b.save(strcat(getenv('LAMP_OUTPUT_DIR'), 'octave_', getenv('OMP_NUM_THREADS'), '.txt'));
