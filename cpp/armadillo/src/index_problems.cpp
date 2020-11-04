#include "../include/benchmarks.h"

using namespace arma;

void loop_naive(const mat& A, const mat& B, dmat& C)
{
  dmat temp = zeros<dmat>(A.n_rows, B.n_cols);
  for (uint32_t i = 0; i < C.n_rows; i++) {
    temp = A * B;
    C(i, 0) = temp(i, i);
  }
}

void loop_recommended(const mat& A, const mat& B, dmat& C)
{
  dmat temp = A * B;
  for (uint32_t i = 0; i < C.n_rows; i++) {
    C(i, 0) = temp(i, i);
  }
}

void bench_index_problems(Benchmarker& b, int n)
{
  auto m = n / 10;
  dmat A = randn<dmat>(m, m);
  dmat B = randn<dmat>(m, m);
  dmat C = randn<dmat>(m, 1);

  b.benchmark("loop_nai", loop_naive, A, B, C);
  b.benchmark("loop_rec", loop_recommended, A, B, C);
}
