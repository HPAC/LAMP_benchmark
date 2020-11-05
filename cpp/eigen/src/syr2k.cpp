#include "../include/benchmarks.h"

using namespace Eigen;

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

void bench_syr2k(Benchmarker &b, int n)
{
  MatrixXd A = MatrixXd::Random(n, n);
  MatrixXd B = MatrixXd::Random(n, n);
  MatrixXd C = MatrixXd::Random(n, n);
  C = C * C.transpose();

  b.benchmark("syr2k_implicit", syr2k_implicit, A, B, C);
  b.benchmark("syr2k_implicit_compact", syr2k_implicit_compact, A, B, C);
  b.benchmark("syr2k_implicit_noup", syr2k_implicit_noup, A, B, C);
  b.benchmark("syr2k_implicit_coeff", syr2k_implicit_coeff, A, B, C);
  b.benchmark("syr2k_implicit_double_coeff", syr2k_implicit_double_coeff, A, B, C);
}
