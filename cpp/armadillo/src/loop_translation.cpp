#include "../include/benchmarks.h"

using namespace arma;

void loop_translation_naive(const mat& A, const mat& B, dmat& C)
{
  for (uint32_t i = 0; i < C.n_cols; i++) {
    C.col(i) = A * B.col(i);
  }
}

void loop_translation_recommended(const mat& A, const mat& B, dmat& C)
{
  C = A * B;
}

void bench_loop_translation(Benchmarker& b, int n)
{
  dmat A = randn<dmat>(n, n);
  dmat B = randn<dmat>(n, n);
  dmat C = randn<dmat>(n, n);

  b.benchmark("loop_translation_nai", loop_translation_naive, A, B, C);
  b.benchmark("loop_translation_rec", loop_translation_recommended, A, B, C);
}
