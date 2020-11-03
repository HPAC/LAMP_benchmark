#include "../lib/benchmarks.h"

static void add(const mat& A, mat& B)
{
  B = A + B;
}

static void scal(mat& A)
{
  A = 3.0 * A;
}

void bench_add_scal(int n, Benchmarker& b)
{
  A = randn<mat>(n, n);
  B = randn<mat>(n, n);

  b.benchmark("add", add, A, B);
  b.benchmark("scal", scal, A);
}
