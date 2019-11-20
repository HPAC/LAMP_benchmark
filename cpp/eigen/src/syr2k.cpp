#include "../lib/syr2k.h"

void syr2k_implicit(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B.transpose() + B * A.transpose() + C;
}

void syr2k_implicit_compact(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C += A * B.transpose() + B * A.transpose();
}

void syr2k_implicit_coeff(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = 3.0 * A * B.transpose() + B * A.transpose() + C;
}

void syr2k_implicit_double_coeff(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = 3.0 * A * B.transpose() + B * A.transpose() + 3.0 * C;
}

void syr2k_implicit_noup(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B.transpose() + B * A.transpose();
}

void bench_syr2k(const MatrixXd& A, const MatrixXd& B, const MatrixXd& C, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> impl_syr2k(LAMP_REPS);
  std::vector<double> impl_syr2k_compact(LAMP_REPS);
  std::vector<double> impl_syr2k_noup(LAMP_REPS);
  std::vector<double> impl_syr2k_coeff(LAMP_REPS);
  std::vector<double> impl_syr2k_double_coeff(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, syr2k_implicit(At, Bt, Ct), impl_syr2k[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, syr2k_implicit_compact(At, Bt, Ct), impl_syr2k_compact[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, syr2k_implicit_noup(At, Bt, Ct), impl_syr2k_noup[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, syr2k_implicit_coeff(At, Bt, Ct), impl_syr2k_coeff[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, syr2k_implicit_double_coeff(At, Bt, Ct), impl_syr2k_double_coeff[i]);
  }

  b.add(impl_syr2k, "syr2k_implicit");
  b.add(impl_syr2k_compact, "syr2k_implicit_compact");
  b.add(impl_syr2k_noup, "syr2k_implicit_noup");
  b.add(impl_syr2k_coeff, "syr2k_implicit_coeff");
  b.add(impl_syr2k_double_coeff, "syr2k_implicit_double_coeff");
}
