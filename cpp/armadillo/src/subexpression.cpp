#include "../lib/subexpression.h"

static void naive(const mat& A, const mat& B, mat& C)
{
  C = A * B + A * B;
}

static void recommended(const mat& A, const mat& B, mat& C)
{
  C = A * B;
  C = C + C;
}

void bench_subexpression(const mat& A, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  dmat C = zeros<dmat>(A.n_rows, B.n_cols);
  dmat D = zeros<dmat>(A.n_rows, B.n_cols);
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

  b.add(naive_v, "subexpr_nai");
  b.add(recommended_v, "subexpr_rec");
}
