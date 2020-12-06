#include "../include/benchmarks.h"

using namespace arma;

void solve_naive(const mat &A, const mat &B, mat &C)
{
  C = A.i() * B;
}

void solve_recommended(const mat &A, const mat &B, mat &C)
{
  solve(C, A, B, solve_opts::fast);
}

void bench_composed_operations(Benchmarker &b, int n)
{
  dmat A = randn<dmat>(n, n);
  dmat B = randn<dmat>(n, 200);
  dmat C = zeros<dmat>(n, 200);
  //dmat c1 = C;
  //dmat c2 = C;
  //naive(A, B, c1);
  //recommended(A, B, c2);
  //std::cout << "Linsolve equal: " << approx_equal(c1, c2, "both", 1e-5, 1e-5) << std::endl;

  b.benchmark("solve_nai", solve_naive, A, B, C);
  b.benchmark("solve_rec", solve_recommended, A, B, C);

  //B = randn<dmat>(n, n / 2);
  //C = zeros<dmat>(n, n / 2);
  //b.benchmark("solve_large_nai", solve_naive, A, B, C);
  //b.benchmark("solve_large_rec", solve_recommended, A, B, C);
}
