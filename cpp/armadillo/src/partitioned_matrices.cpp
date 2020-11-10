#include "../include/benchmarks.h"

using namespace arma;

void implicit_partitioned(const mat& A1, const mat& A2, const mat& B, mat& C)
{
  C = solve(join_vert(join_horiz(A1, zeros(A1.n_rows, A1.n_cols)), join_horiz(zeros(A2.n_rows, A2.n_cols), A2)), B, solve_opts::fast);
}

void explicit_partitioned(const mat& A1, const mat& A2, const mat& B, mat& C)
{
  dmat b1 = B(span(0, A1.n_rows - 1), span(0, B.n_cols - 1));
  dmat b2 = B(span(A1.n_rows, B.n_rows - 1), span(0, B.n_cols - 1));
  C = join_vert(solve(A1, b1, solve_opts::fast), solve(A2, b2, solve_opts::fast));
}

void bench_partitioned_matrices(Benchmarker& b, int n)
{
  auto m = n / 2;
  dmat A1 = randn<dmat>(m, m);
  dmat A2 = randn<dmat>(m, m);
  dmat B = randn<dmat>(2 * m, 2 * m);
  dmat C = zeros<dmat>(2 * m, 2 * m);

  //dmat c1 = C;
  //dmat c2 = C;
  //implicit_partitioned(A1, A2, B, c1);
  //explicit_partitioned(A1, A2, B, c2);
  //std::cout << "Linsolve equal: " << approx_equal(c1, c2, "both", 1e-5, 1e-5) << std::endl;

  b.benchmark("compact", implicit_partitioned, A1, A2, B, C);
  b.benchmark("blocked", explicit_partitioned, A1, A2, B, C);
}
