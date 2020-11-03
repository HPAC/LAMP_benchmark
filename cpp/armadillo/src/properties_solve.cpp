#include "../lib/benchmarks.h"

static void my_solve(dmat &C, dmat &A, dmat &B)
{
  solve(C, A, B, solve_opts::fast);
}

void bench_properties_solve(int m, int rhs, Benchmarker& b)
{
  dmat B = randn<dmat>(m, rhs);
  dmat C = zeros<dmat>(m, rhs);

  dmat A = randn<dmat>(m, m);
  A = A + trans(A) - diagmat(A) + eye<dmat>(m, m) * m;
  std::cout << "A symmetric: " << A.is_symmetric() << std::endl;
  std::cout << "A is SPD   : " << A.is_sympd(1e-5) << std::endl;

  b.benchmark("solve_spd", my_solve, C, A, B);

  A = randn<dmat>(m, m);
  A = A + trans(A) - diagmat(A);
  A(0, 0) = -1.0;
  std::cout << "A symmetric: " << A.is_symmetric() << std::endl;
  std::cout << "A is SPD   : " << A.is_sympd() << std::endl;

  b.benchmark("solve_sym", my_solve, C, A, B);

  A = randn<dmat>(m, m);
  A = trimatl(A);
  std::cout << "A lower triangular: " << approx_equal(A, trimatl(A), "both", 1e-10, 1e-10) << std::endl;

  b.benchmark("solve_tri", my_solve, C, A, B);

  A = randn<dmat>(m, m);
  A = diagmat(A);
  std::cout << "A diagonal: " << approx_equal(A, diagmat(A), "both", 1e-10, 1e-10) << std::endl;

  b.benchmark("solve_dia", my_solve, C, A, B);
}
