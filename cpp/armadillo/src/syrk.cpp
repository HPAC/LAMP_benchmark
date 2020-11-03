#include "../lib/benchmarks.h"

void syrk_implicit(const mat& A, mat& C)
{
  C = A * trans(A) + C;
}

void syrk_implicit_compact(const mat& A, mat& C)
{
  C += A * trans(A);
}

void syrk_implicit_noup(const mat& A, mat& C)
{
  C = A * trans(A);
}

void bench_syrk(int n, int k, Benchmarker& b)
{
  A = randn<dmat>(n, k);
  C = randn<dmat>(n, n);
  C = C * trans(C);

  b.benchmark("syrk_implicit", syrk_implicit, A, C);
  b.benchmark("syrk_implicit_compact", syrk_implicit_compact, A, C);
  b.benchmark("syrk_implicit_noup", syrk_implicit_noup, A, C);
}
