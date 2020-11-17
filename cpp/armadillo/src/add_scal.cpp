#include "../include/benchmarks.h"

using namespace arma;

static void add(const mat& A, mat& B)
{
  B = A + B;
}

static void scal(mat& A)
{
  A = 3.0 * A;
}

void bench_add_scal(Benchmarker& b, int n)
{
  dmat A = randn<dmat>(n, n);
  dmat B = randn<dmat>(n, n);

  b.benchmark("add", add, A, B);
  b.benchmark("scal", scal, A);
}
