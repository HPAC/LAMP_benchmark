#include "../include/benchmarks.h"

using namespace arma;

void my_solve(dmat &C, sp_dmat &A, dmat &B)
{
  spsolve(C, A, B);
}

void sym_solve(dmat &C, sp_dmat &A, dmat &B)
{
  superlu_opts sp;
  sp.symmetric = true;
  spsolve(C, A, B, "superlu", sp);
}

void bench_properties_solve_sparse(Benchmarker& b, int n, double density)
{
  dmat B = randn(n, 10);
  dmat C = randn(n, 10);

  std::cout << "Sparse experiments" << std::endl;

  sp_dmat A = sprandn(n, n, density);
  A += speye<sp_dmat>(n, n);
  b.benchmark("solve_sp_gen", my_solve, C, A, B);

  A = sprandn(n, n, density/2);
  A = A + trans(A) + speye<sp_dmat>(n,n);
  res = (A.is_symmetric()) ? "true" : "false";
  std::cout << "A symmetric: " << res << std::endl;
  b.benchmark("solve_sp_sym", my_solve, C, A, B);

  res = (A.is_symmetric()) ? "true" : "false";
  std::cout << "A symmetric: " << res << std::endl;
  b.benchmark("solve_sp_sym_rec", sym_solve, C, A, B);

  A = sprandn(n, n, density/2);
  A = A + trans(A) + n * speye<sp_dmat>(n,n);
  res = (A.is_symmetric()) ? "true" : "false";
  std::cout << "A symmetric: " << res << std::endl;
  b.benchmark("solve_sp_spd", my_solve, C, A, B);

  A = sprandn(n, n, 2*density);
  A += speye<sp_dmat>(n, n);
  sp_dmat Atr = trimatl(A);
  std::string res = (approx_equal(Atr, trimatl(A), "both", 1e-10, 1e-10)) ? "true" : "false";
  std::cout << "A lower triangular: " << res << std::endl;
  b.benchmark("solve_sp_tri", my_solve, C, Atr, B);
}
