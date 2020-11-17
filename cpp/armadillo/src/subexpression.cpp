#include "../include/benchmarks.h"

using namespace arma;

void subexpression_naive(const mat& A, const mat& B, mat& C)
{
  C = A * B + A * B;
}

void subexpression_recommended(const mat& A, const mat& B, mat& C)
{
  C = A * B;
  C = C + C;
}

void bench_subexpression(Benchmarker& b, int n)
{
  dmat A = randn<mat>(n, n);
  dmat B = randn<mat>(n, n);
  dmat C = zeros<dmat>(n, n);

  b.benchmark("subexpr_nai", subexpression_naive, A, B, C);
  b.benchmark("subexpr_rec", subexpression_recommended, A, B, C);
}
