#include "../lib/matrix_chain.h"

void l_r_orig(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = m * A * B;
}

void l_r_guid(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = (m * A) * B;
}

void r_l_orig(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = A * B * m;
}

void r_l_guid(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m, MatrixXd& C)
{
  C = A * (B * m);
}

void mixed_orig(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m1, const MatrixXd& m2, MatrixXd& C)
{
  C = A * m1 * m2 * B;
}
void mixed_guid(const MatrixXd& A, const MatrixXd& B, const MatrixXd& m1, const MatrixXd& m2, MatrixXd& C)
{
  C = (A * m1) * (m2 * B);
}

void bench_matrix_chain(const MatrixXd& A, const MatrixXd& B, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  //int m = A.rows();
  int k = A.cols();
  //int n = B.cols();

  MatrixXd m1 = MatrixXd::Random(k / 2, A.rows());
  MatrixXd m2 = MatrixXd::Random(B.cols(), k / 2);

  std::vector<double> l_r_orig_v(LAMP_REPS);
  std::vector<double> l_r_guid_v(LAMP_REPS);
  std::vector<double> r_l_orig_v(LAMP_REPS);
  std::vector<double> r_l_guid_v(LAMP_REPS);
  std::vector<double> mixed_orig_v(LAMP_REPS);
  std::vector<double> mixed_guid_v(LAMP_REPS);

  MatrixXd C = MatrixXd::Zero(k / 2, B.cols());
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd m1t = m1;
    MatrixXd Ct = C;

    BENCHMARK(b, l_r_orig(At, Bt, m1t, Ct), l_r_orig_v[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd m1t = m1;
    MatrixXd Ct = C;

    BENCHMARK(b, l_r_guid(At, Bt, m1t, Ct), l_r_guid_v[i]);
  }

  C = MatrixXd::Zero(A.rows(), k / 2);
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd m2t = m2;
    MatrixXd Ct = C;

    BENCHMARK(b, r_l_orig(At, Bt, m2t, Ct), r_l_orig_v[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd m2t = m2;
    MatrixXd Ct = C;

    BENCHMARK(b, r_l_guid(At, Bt, m2t, Ct), r_l_guid_v[i]);
  }

  C = MatrixXd::Zero(A.rows(), B.cols());
  m1 = MatrixXd::Random(A.cols(), k / 2);
  m2 = MatrixXd::Random(k / 2, B.rows());
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd m1t = m1;
    MatrixXd m2t = m2;
    MatrixXd Ct = C;

    BENCHMARK(b, mixed_orig(At, Bt, m1t, m2t, Ct), mixed_orig_v[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd m1t = m1;
    MatrixXd m2t = m2;
    MatrixXd Ct = C;

    BENCHMARK(b, mixed_guid(At, Bt, m1t, m2t, Ct), mixed_guid_v[i]);
  }

  b.add(l_r_orig_v, "mc_l_r_orig");
  b.add(l_r_guid_v, "mc_l_r_guid");
  b.add(r_l_orig_v, "mc_r_l_orig");
  b.add(r_l_guid_v, "mc_r_l_guid");
  b.add(mixed_orig_v, "mc_mixed_orig");
  b.add(mixed_guid_v, "mc_mixed_guid");
}
