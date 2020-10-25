addpath(getenv('LAMP_OCTAVE_DIR'))
import MatrixGenerator.Benchmarker;

m = 3000;
k = 550;
n = 3000;

tn = 80;
ipn = 80;
l = 100;
p = 1500;

b = Benchmarker();

A = randn(n,n);
B = randn(n,n);
add_scal(A, B, b);

properties_solve(m, l, b);

A = randn(n,k);
C = randn(n,n); C = C+C';
kernel_invocations_syrk(A, C, b);

A = randn(m,k);
B = randn(k,n);
C = randn(m,n);
kernel_invocations_gemm(A, B, C, b);

A = randn(n,k);
B = randn(n,k);
C = randn(n,n); C = C+C';
kernel_invocations_syr2k(A, B, C, b);

A = randn(tn,tn);
B = randn(tn,tn);
C = randn(tn,tn);
transposition(A, B, C, b);

A = randn(m,k);
B = randn(k,n);
common_subexpressions(A, B, b);

A = randn(n,n);
B = randn(n,l);
solve_linear_systems(A, B, b);

A = randn(m,k);
B = randn(k,n);
matrix_chain(A, B, b);

A = randn(n,n);
B = randn(n,n);
diagonal_elements(A, B, b);

A = randn(n,n);
B = randn(n,n);
partial_operand(A, B, b);

A = randn(ipn,ipn);
B = randn(ipn,ipn);
C = randn(ipn,1);
index_problems(A, B, C, b);

A = randn(n,n);
B = randn(n,n);
C = randn(n,n);
loop_translation(A, B, C, b);

A1 = randn(p,p);
A2 = randn(p,p);
B = randn(2*p,2*p);
partitioned_matrices(A1, A2, B, b);

b.save(strcat(getenv('LAMP_OUTPUT_DIR'), 'octave', '.txt'));
