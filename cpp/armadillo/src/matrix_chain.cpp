#include "../lib/matrix_chain.h"

void l_r_orig(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = m * A * B;
}

void l_r_guid(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = (m * A) * B;
}

void r_l_orig(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = A * B * m;
}

void r_l_guid(const mat& A, const mat& B, const mat& m, mat& C)
{
  C = A * (B * m);
}

void mixed_orig(const mat& A, const mat& B, const mat& m1, const mat& m2, mat& C)
{
  C = A * m1 * m2 * B;
}

void mixed_guid(const mat& A, const mat& B, const mat& m1, const mat& m2, mat& C)
{
  C = (A * m1) * (m2 * B);
}

void bench_matrix_chain(const mat& A, const mat& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;

  int m = A.n_rows;
  int k = A.n_cols;
  int n = B.n_cols;

  dmat m1 = randn<dmat>(k / 2, m);
  dmat m2 = randn<dmat>(n, k / 2);

  // timings vectors
  std::vector<double> l_r_orig_v(LAMP_REPS);
  std::vector<double> l_r_guid_v(LAMP_REPS);
  std::vector<double> r_l_orig_v(LAMP_REPS);
  std::vector<double> r_l_guid_v(LAMP_REPS);
  std::vector<double> mixed_orig_v(LAMP_REPS);
  std::vector<double> mixed_guid_v(LAMP_REPS);

  // ->
  dmat C = zeros<dmat>(m1.n_rows, B.n_cols);
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat m1t = m1;
    dmat Ct = C;

    BENCHMARK(b, l_r_orig(At, Bt, m1t, Ct), l_r_orig_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat m1t = m1;
    dmat Ct = C;

    BENCHMARK(b, l_r_guid(At, Bt, m1t, Ct), l_r_guid_v[i]);
  }

  // <-
  C = zeros<dmat>(A.n_rows, m2.n_cols);
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat m2t = m2;
    dmat Ct = C;

    BENCHMARK(b, r_l_orig(At, Bt, m2t, Ct), r_l_orig_v[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat m2t = m2;
    dmat Ct = C;

    BENCHMARK(b, r_l_guid(At, Bt, m2t, Ct), r_l_guid_v[i]);
  }

  // Mixed
  C = zeros<dmat>(A.n_rows, B.n_cols);
  m1 = randn<dmat>(A.n_cols, k / 2);
  m2 = randn<dmat>(k / 2, B.n_rows);
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat m1t = m1;
    dmat m2t = m2;
    dmat Ct = C;

    BENCHMARK(b, mixed_orig(At, Bt, m1t, m2t, Ct), mixed_orig_v[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    dmat At = A;
    dmat Bt = B;
    dmat m1t = m1;
    dmat m2t = m2;
    dmat Ct = C;

    BENCHMARK(b, mixed_guid(At, Bt, m1t, m2t, Ct), mixed_guid_v[i]);
  }

  b.add(l_r_orig_v, "mc_l_r_orig");
  b.add(l_r_guid_v, "mc_l_r_guid");
  b.add(r_l_orig_v, "mc_r_l_orig");
  b.add(r_l_guid_v, "mc_r_l_guid");
  b.add(mixed_orig_v, "mc_mixed_orig");
  b.add(mixed_guid_v, "mc_mixed_guid");
}
