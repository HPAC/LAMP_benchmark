#include "../include/benchmarks.h"

using namespace arma;

static void my_solve(dmat &C, sp_dmat &A, dmat &B)
{
  spsolve(C, A, B);
}

void bench_properties_solve_sparse(Benchmarker& b, int n, double sparsity)
{
  dmat B = randn(n, 10);
  dmat C = randn(n, 10);

  sp_dmat A = sprandn(n, n, sparsity/2);
  A += 0.01 * speye<sp_dmat>(n, n);
  std::cout << "A symmetric: " << A.is_symmetric() << std::endl;
  b.benchmark("solve_sp_gen", my_solve, C, A, B);

  A = A + trans(A) + speye<sp_dmat>(n, n);
  A(0, 0) = -1.0;
  std::cout << "A symmetric: " << A.is_symmetric() << std::endl;
  b.benchmark("solve_sp_sym", my_solve, C, A, B);

  A = sprandn(n, n, sparsity/2);
  A = A + trans(A) + speye<sp_dmat>(n, n) * n;
  std::cout << "A symmetric: " << A.is_symmetric() << std::endl;
  b.benchmark("solve_sp_spd", my_solve, C, A, B);

  A = sprandn(n, n, sparsity);
  A = A + speye<sp_dmat>(n, n);
  sp_dmat test = trimatl(A);
  std::cout << "A lower triangular: " << approx_equal(test, trimatl(A), "both", 1e-10, 1e-10) << std::endl;
  b.benchmark("solve_sp_tri", my_solve, C, A, B);
}
