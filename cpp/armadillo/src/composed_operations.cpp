#include "../lib/composed_operations.h"

static void naive(const mat& A, const mat& B, mat& C)
{
  C = A.i() * B;
}

static void recommended(const mat& A, const mat& B, mat& C)
{
  solve(C, A, B, solve_opts::fast);
}

static void recommended_spd(const mat& A, const mat& B, mat& C)
{
  solve(C, symmatu(A), B, solve_opts::fast);
}

static void naive_spd(const mat& A, const mat& B, mat& C)
{
  C = symmatu(A).i() * B;
}

void bench_composed_operations(const mat& A, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  dmat C = zeros<dmat>(A.n_cols, B.n_rows);
  std::vector<double> naive_v(LAMP_REPS);
  std::vector<double> recommended_v(LAMP_REPS);
  std::vector<double> naive_large_v(LAMP_REPS);
  std::vector<double> recommended_large_v(LAMP_REPS);
  std::vector<double> naive_spd_v(LAMP_REPS);
  std::vector<double> recommended_spd_v(LAMP_REPS);
  std::vector<double> naive_spd_all_v(LAMP_REPS);
  std::vector<double> recommended_spd_all_v(LAMP_REPS);
  //dmat c1 = C;
  //dmat c2 = C;
  //naive(A, B, c1);
  //recommended(A, B, c2);
  //std::cout << "Linsolve equal: " << approx_equal(c1, c2, "both", 1e-5, 1e-5) << std::endl;

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
    dmat temp = ones<dmat>(size(A));
    dmat At = A * trans(A);
    At += diagmat(temp) * At.n_cols;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, naive(At, Bt, Ct), naive_spd_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat temp = ones<dmat>(size(A));
    dmat At = A * trans(A);
    At += diagmat(temp) * At.n_cols;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, recommended(At, Bt, Ct), recommended_spd_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat temp = ones<dmat>(size(A));
    dmat At = A * trans(A);
    At += diagmat(temp) * At.n_cols;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, naive_spd(At, Bt, Ct), naive_spd_all_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat temp = ones<dmat>(size(A));
    dmat At = A * trans(A);
    At += diagmat(temp) * At.n_cols;
    dmat Bt = B;
    dmat Ct = C;

    BENCHMARK(b, recommended_spd(At, Bt, Ct), recommended_spd_all_v[i]);
  }

  dmat Bl = randn<mat>(B.n_rows, 2 * A.n_rows);
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = Bl;
    dmat Ct = C;

    BENCHMARK(b, naive(At, Bt, Ct), naive_large_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = Bl;
    dmat Ct = C;

    BENCHMARK(b, recommended(At, Bt, Ct), recommended_large_v[i]);
  }

  b.add(naive_v, "solve_nai");
  b.add(recommended_v, "solve_rec");
  b.add(naive_large_v, "solve_large_nai");
  b.add(recommended_large_v, "solve_large_rec");
  b.add(naive_spd_v, "solve_nai_spd");
  b.add(recommended_spd_v, "solve_rec_spd");
  b.add(naive_spd_all_v, "solve_nai_spd_all");
  b.add(recommended_spd_all_v, "solve_rec_spd_all");
}
