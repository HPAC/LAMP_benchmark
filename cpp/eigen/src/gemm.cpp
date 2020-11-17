#include "../include/benchmarks.h"

using namespace Eigen;

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

void bench_gemm(Benchmarker &b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);
  MatrixXd C = MatrixXd::Random(n, n);

  b.benchmark("gemm_implicit", gemm_implicit, A, B, C);
  b.benchmark("gemm_implicit_compact", gemm_implicit_compact, A, B, C);
  b.benchmark("gemm_implicit_noup", gemm_implicit_noup, A, B, C);
  b.benchmark("gemm_implicit_coeff", gemm_implicit_coeff, A, B, C);
  b.benchmark("gemm_implicit_double_coeff", gemm_implicit_double_coeff, A, B, C);

  A.setRandom(n, n);
  A = A.triangularView<Eigen::Lower>(); // This step creates a full matrix from the view.
  b.benchmark("trmm_implicit", trmm_implicit, A, B);
  b.benchmark("trmm_implicit_compact", trmm_implicit_compact, A, B);
  b.benchmark("trmm_implicit_eig", trmm_implicit_eig, A, B);

  A.setRandom(n, n);
  A = A.diagonal().asDiagonal();
  b.benchmark("diagmm", diagmm, A, B, C);
}
