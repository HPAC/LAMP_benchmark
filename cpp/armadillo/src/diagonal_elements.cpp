#include "../lib/diagonal_elements.h"

static void naive(const mat& A, const mat& B, mat& C)
{
  C = diagvec(A + B);
}

static void recommended(const mat& A, const mat& B, mat& C)
{
  C = diagvec(A) + diagvec(B);
}

static void naive_mult(const mat& A, const mat& B, mat& C)
{
  C = diagvec(A * B);
}

void bench_diagonal_elements(const mat& A, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  dmat C = zeros<dmat>(A.n_rows, A.n_cols);
  std::vector<double> naive_v(LAMP_REPS);
  std::vector<double> recommended_v(LAMP_REPS);
  std::vector<double> naive_mult_v(LAMP_REPS);

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

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, naive_mult(At, Bt, Ct), naive_mult_v[i]);
  }
  b.add(naive_v, "diag_add_nai");
  b.add(recommended_v, "diag_add_rec");
  b.add(naive_mult_v, "diag_mult_nai");
}
