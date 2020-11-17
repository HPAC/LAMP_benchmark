#include "../include/benchmarks.h"

using namespace Eigen;

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

void bench_syrk(Benchmarker &b, int n)
{
  auto A = MatrixXd::Random(n, n);
  auto C = MatrixXd::Random(n, n);
  MatrixXd Cs = C * C.transpose();

  b.benchmark("syrk_implicit", syrk_implicit, A, Cs);
  b.benchmark("syrk_implicit_compact", syrk_implicit_compact, A, Cs);
  b.benchmark("syrk_implicit_noup", syrk_implicit_noup, A, Cs);
}
