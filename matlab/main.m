% If the input arguments of a function in matlab are arrays, they are passed by reference unless you modify the data inside the function. In that case, a copy of the matrix is created somewhere else, and the modified data are stored. This modified data is lost, unless the user returns the matrix he modified and assigns it back to the caller matrix. Reference [[https://de.mathworks.com/help/matlab/matlab_prog/memory-allocation.html]] for more information
addpath(getenv('LAMP_MATLAB_DIR'))
import MatrixGenerator.*;

n = maxNumCompThreads();
if n ~= 1
  n = maxNumCompThreads(str2num(getenv('OMP_NUM_THREADS')));
end
n = maxNumCompThreads();
fprintf('Threads = %d', n)

n = str2num(getenv('LAMP_N'));

b = Benchmarker();

A = randn(n,n);
B = randn(n,n);
add_scal(A, B, b);

properties_solve(n, 200, b);

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
B = randn(n,200);
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

A1 = randn(n / 2,n / 2);
A2 = randn(n / 2,n / 2);
B = randn(n,n);
partitioned_matrices(A1, A2, B, b);

b.save(strcat(getenv('LAMP_OUTPUT_DIR'), 'matlab_', getenv('OMP_NUM_THREADS'), '.txt'));
