#include "../lib/gemm.h"

void gemm_implicit(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B + C;
}

void gemm_implicit_compact(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C += A * B;
}

void gemm_implicit_coeff(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C += 3.0 * A * B;
}

void gemm_implicit_double_coeff(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = 3.0 * A * B + 3.0 * C;
}

void gemm_implicit_noup(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B;
}

void trmm_implicit_compact(const MatrixXd& A, MatrixXd& B)
{
  B *= A;
}

void trmm_implicit(const MatrixXd& A, MatrixXd& B)
{
  B = A * B;
}

void trmm_implicit_eig(const MatrixXd& A, MatrixXd& B)
{
  B = A.triangularView<Eigen::Lower>() * B;
}

void diagmm(const MatrixXd& A, const MatrixXd& B, MatrixXd& C)
{
  C = A * B;
}

void bench_gemm(const MatrixXd& A, const MatrixXd& B, const MatrixXd& C, Benchmarker& b)
{

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::vector<double> impl_gemm(LAMP_REPS);
  std::vector<double> impl_gemm_compact(LAMP_REPS);
  std::vector<double> impl_gemm_noup(LAMP_REPS);
  std::vector<double> impl_gemm_coeff(LAMP_REPS);
  std::vector<double> impl_gemm_double_coeff(LAMP_REPS);

  std::vector<double> gemm_prop(LAMP_REPS);
  std::vector<double> impl_trmm(LAMP_REPS);
  std::vector<double> impl_trmm_compact(LAMP_REPS);
  std::vector<double> impl_diagmm(LAMP_REPS);

  std::vector<double> impl_trmm_eig(LAMP_REPS);

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, gemm_implicit(At, Bt, Ct), impl_gemm[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, gemm_implicit_compact(At, Bt, Ct), impl_gemm_compact[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, gemm_implicit_noup(At, Bt, Ct), impl_gemm_noup[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, gemm_implicit_coeff(At, Bt, Ct), impl_gemm_coeff[i]);
  }
  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = A;
    MatrixXd Bt = B;
    MatrixXd Ct = C;

    BENCHMARK(b, gemm_implicit_double_coeff(At, Bt, Ct), impl_gemm_double_coeff[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = MatrixXd::Random(A.rows(), A.rows());
    At = At.triangularView<Eigen::Lower>(); // This step creates a full matrix from the view.
    MatrixXd Bt = MatrixXd::Random(A.rows(), A.rows());

    BENCHMARK(b, trmm_implicit(At, Bt), impl_trmm[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = MatrixXd::Random(A.rows(), A.rows());
    At = At.triangularView<Eigen::Lower>(); // This step creates a full matrix from the view.
    MatrixXd Bt = MatrixXd::Random(A.rows(), A.rows());

    BENCHMARK(b, trmm_implicit_compact(At, Bt), impl_trmm_compact[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = MatrixXd::Random(A.rows(), A.rows());
    At = At.triangularView<Eigen::Lower>();
    MatrixXd Bt = MatrixXd::Random(A.rows(), A.rows());

    BENCHMARK(b, trmm_implicit_eig(At, Bt), impl_trmm_eig[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = MatrixXd::Random(A.rows(), A.rows());
    MatrixXd Atd = At.diagonal().asDiagonal();
    MatrixXd Bt = MatrixXd::Random(A.rows(), A.rows());
    MatrixXd Ct = MatrixXd::Random(A.rows(), A.rows());

    BENCHMARK(b, diagmm(Atd, Bt, Ct), impl_diagmm[i]);
  }

  for (auto i = 0; i < LAMP_REPS; i++) {
    MatrixXd At = MatrixXd::Random(A.rows(), A.rows());
    MatrixXd Bt = MatrixXd::Random(A.rows(), A.rows());
    MatrixXd Ct = MatrixXd::Random(A.rows(), A.rows());

    BENCHMARK(b, gemm_implicit_noup(At, Bt, Ct), gemm_prop[i]);
  }

  b.add(impl_gemm, "gemm_implicit");
  b.add(impl_gemm_compact, "gemm_implicit_compact");
  b.add(impl_gemm_noup, "gemm_implicit_noup");
  b.add(impl_gemm_coeff, "gemm_implicit_coeff");
  b.add(impl_gemm_double_coeff, "gemm_implicit_double_coeff");

  b.add(gemm_prop, "gemm_prop");
  b.add(impl_trmm, "trmm_implicit");
  b.add(impl_trmm_compact, "trmm_implicit_compact");
  b.add(impl_diagmm, "diagmm");

  b.add(impl_trmm_eig, "trmm_implicit_eig");
}
