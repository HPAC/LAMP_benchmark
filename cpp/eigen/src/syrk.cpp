#include "../lib/syrk.h"

void syrk_implicit(const MatrixXd& A, MatrixXd& C)
{
  C = A * A.transpose() + C;
}

void syrk_implicit_compact(const MatrixXd& A, MatrixXd& C)
{
  C += A * A.transpose();
}

void syrk_implicit_noup(const MatrixXd& A, MatrixXd& C)
{
  C = A * A.transpose();
}

void bench_syrk(const MatrixXd& A, const MatrixXd& C, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> impl_syrk(LAMP_REPS);
  std::vector<double> impl_syrk_noup(LAMP_REPS);
  std::vector<double> impl_syrk_compact(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Ct = C;

    BENCHMARK(b, syrk_implicit(At, Ct), impl_syrk[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Ct = C;

    BENCHMARK(b, syrk_implicit_compact(At, Ct), impl_syrk_compact[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Ct = C;

    BENCHMARK(b, syrk_implicit_noup(At, Ct), impl_syrk_noup[i]);
  }
  b.add(impl_syrk, "syrk_implicit");
  b.add(impl_syrk_compact, "syrk_implicit_compact");
  b.add(impl_syrk_noup, "syrk_implicit_noup");
}
