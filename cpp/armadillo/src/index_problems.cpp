#include "../lib/index_problems.h"

static void naive(const mat& A, const mat& B, dmat& C)
{
  dmat temp = zeros<dmat>(A.n_rows, B.n_cols);
  for (uint32_t i = 0; i < C.n_rows; i++) {
    temp = A * B;
    C(i, 0) = temp(i, i);
  }
}

static void recommended(const mat& A, const mat& B, dmat& C)
{
  dmat temp = A * B;
  for (uint32_t i = 0; i < C.n_rows; i++) {
    C(i, 0) = temp(i, i);
  }
}

void bench_index_problems(const mat& A, const mat& B, const mat& C, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> naive_v(LAMP_REPS);
  std::vector<double> recommended_v(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, naive(At, Bt, Ct), naive_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, recommended(At, Bt, Ct), recommended_v[i]);
  }

  b.add(naive_v, "loop_nai");
  b.add(recommended_v, "loop_rec");
}
